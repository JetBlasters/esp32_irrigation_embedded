//
// Created by rgray on 6/02/2023.
//

#include "driver/gpio.h"
#include "ShitRegister.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

shift_register::shift_register(gpio_num_t ser, gpio_num_t rclk, gpio_num_t srclk) : ser(ser), rclk(rclk), srclk(srclk){
    gpio_set_direction(ser, GPIO_MODE_OUTPUT);
    gpio_set_direction(rclk, GPIO_MODE_OUTPUT);
    gpio_set_direction(srclk, GPIO_MODE_OUTPUT);
    gpio_set_level(rclk, 1);
    gpio_set_level(ser, 0);
    gpio_set_level(srclk, 0);
    output(0);
}

void shift_register::output(int8_t output) {
    for (int position = 0; position <= 7; position ++) {
        int out = (output & (1 << position)) >> position;
        gpio_set_level(srclk,0);
        gpio_set_level(ser, out);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        gpio_set_level(srclk, 1);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    gpio_set_level(rclk, 0);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(rclk, 1);
}

void shift_register::add_station(int station) {
    if (std::find(stationsEnabled.begin(), stationsEnabled.end(), station) != stationsEnabled.end()) {
        // already added
        return;
    }

    stationsEnabled.push_back(station);
}

void shift_register::remove_station(int station) {
    auto it = std::find(stationsEnabled.begin(), stationsEnabled.end(), station);
    if (it == stationsEnabled.end()) {
        // already removed
        return;
    }

    stationsEnabled.erase(it);
}

void shift_register::update_output() {
    short out = 0;
    for (int station : stationsEnabled) {
        out |= (1 << (station - 1));
    }

    output(out);
}
