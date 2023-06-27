/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <esp_task_wdt.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "settings.h"

#include "nvs_flash.h"
#include "nvs.h"
#include <memory>
#include <ctime>

#include "smbus.h"
#include "i2c-lcd1602.h"
#include "ButtonHandler.h"
#include "NavigationManager.h"
#include "SettingsPage.h"
#include "MainPage.h"
#include "ShitRegister.h"
#include "DateTimePage.h"
#include "TimeField.h"

extern "C" {
    void app_main();
}

#define WDT_TIMEOUT 10

#define LCD_NUM_ROWS               4
#define LCD_NUM_COLUMNS            40
#define LCD_NUM_VISIBLE_COLUMNS    20


#define I2C_MASTER_NUM           I2C_NUM_0
#define I2C_MASTER_TX_BUF_LEN    0                     // disabled
#define I2C_MASTER_RX_BUF_LEN    0                     // disabled
#define I2C_MASTER_FREQ_HZ       100000
#define I2C_MASTER_SDA_IO        CONFIG_I2C_MASTER_SDA
#define I2C_MASTER_SCL_IO        CONFIG_I2C_MASTER_SCL

#define LEFT_BUTTON GPIO_NUM_21
#define RIGHT_BUTTON GPIO_NUM_22
#define SELECT_BUTTON GPIO_NUM_19
#define BACK_BUTTON GPIO_NUM_18

#define SER GPIO_NUM_25
#define RCLK GPIO_NUM_26
#define SRCLK GPIO_NUM_27

static void i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_DISABLE;  // GY-2561 provides 10kΩ pullups
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_DISABLE;  // GY-2561 provides 10kΩ pullups
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_MASTER_RX_BUF_LEN,
                       I2C_MASTER_TX_BUF_LEN, 0);
}

bool buttonPressed = 0;
int numPressed = 0;


void lcd1602_task(void * pvParameter) {
    // Set up I2C
    i2c_master_init();
    i2c_port_t i2c_num = I2C_MASTER_NUM;
    uint8_t address = CONFIG_LCD1602_I2C_ADDRESS;

    // Set up the SMBus
    smbus_info_t *smbus_info = smbus_malloc();
    ESP_ERROR_CHECK(smbus_init(smbus_info, i2c_num, address));
    ESP_ERROR_CHECK(smbus_set_timeout(smbus_info, 1000 / portTICK_PERIOD_MS));

    // Set up the LCD1602 device with backlight on
    i2c_lcd1602_info_t *lcd_info = i2c_lcd1602_malloc();
    ESP_ERROR_CHECK(i2c_lcd1602_init(lcd_info, smbus_info, true,
                                     LCD_NUM_ROWS, LCD_NUM_COLUMNS, LCD_NUM_VISIBLE_COLUMNS));

    ESP_ERROR_CHECK(i2c_lcd1602_reset(lcd_info));

    i2c_lcd1602_clear(lcd_info);

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%uMB %s flash\n", flash_size / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    std::shared_ptr<MainPage> defaultPage(new MainPage(lcd_info));
    push_page(defaultPage);

    while (true) {
        std::shared_ptr<Page> page = current_page();

        page->page_loop();

        if (is_button_pressed(BACK_BUTTON)) {
            page -> handle_back();
        }

        if (is_button_pressed(SELECT_BUTTON)) {
            page -> handle_select();
        }

        if (is_button_pressed(LEFT_BUTTON)) {
            page -> handle_left();
        }

        if (is_button_pressed(RIGHT_BUTTON)) {
            page -> handle_right();
        }

        // delays approx 100ms
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}


void app_main(void)
{
    esp_err_t err = nvs_flash_init();
    ESP_ERROR_CHECK(err);

    settings::set_time(1675861521);
    add_button(BACK_BUTTON);
    add_button(SELECT_BUTTON);
    add_button(LEFT_BUTTON);
    add_button(RIGHT_BUTTON);

    xTaskCreate(&lcd1602_task, "lcd1602_task", 4096, nullptr, 5, nullptr);

    settings::spiffs_init();


    int output = 0;
    shift_register shift_register(SER, RCLK, SRCLK);

    while (true) {
        vector<shared_ptr<Job>> jobs;
        settings::retrieve_jobs(&jobs);

        time_t currentTime = settings::get_time();

        struct tm* timeinfo;
        timeinfo = localtime(&currentTime);


        unsigned int time = timeinfo->tm_hour * SecondsInAnHour + timeinfo->tm_min * SecondsInAMinute + timeinfo->tm_sec;

        // TODO make the week change on a monday
        bool week = (timeinfo->tm_yday/7) % 2;

        auto day = static_cast<Job::DayOfWeek>(timeinfo->tm_wday % 7);

        for (const shared_ptr<Job>& job : jobs) {
            unique_ptr<Job::Run> currentRun;

            if ((currentRun = job->getCurrentRun(time, day, week)) != nullptr) {
                printf("Running job %s.\n", job->getName().c_str());

                vector<int> activeStations = job->getActiveStations(*currentRun, time, day);

                for (int station : activeStations) {
                    shift_register.add_station(station);
                }
            }
        }

        shift_register.update_output();

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
