//
// Created by rgray on 8/02/2023.
//

#include "DateTimePage.h"
#include "settings.h"
#include <sstream>
#include <string>
#include "esp_timer.h"
#include "FieldOption.h"
#include "FunctionalOption.h"
#include "NavigationManager.h"
#include <ctime>

//void DateTimePage::timer_isr_handler(void* arg) {
//    flash = !flash;
//}

DateTimePage::DateTimePage(i2c_lcd1602_info_t *_lcd_info) : OptionsPage(_lcd_info) {
    time_t now = settings::get_time();

    tm timeinfo{};

    localtime_r(&now, &timeinfo);

    time = std::make_shared<unsigned int>(timeinfo.tm_hour*(SecondsInAnHour) + timeinfo.tm_min*(SecondsInAMinute));
    Date d = {static_cast<unsigned short>(timeinfo.tm_mday),
              static_cast<unsigned short>(timeinfo.tm_mon + 1),
              static_cast<unsigned short>(timeinfo.tm_year - 100)};
    date = std::make_shared<Date>(d);

    add_option(std::make_shared<fieldOption>("Time", std::make_unique<TimeField>(time)));
    add_option(std::make_shared<fieldOption>("Date", std::make_unique<DateField>(date)));
    add_option(std::make_shared<functionalOption>("Save...", [this] {
        save_time();
    }));


    //    const esp_timer_create_args_t flash_timer_args = {
//            .callback = &timer_isr_handler,
//            /* name is optional, but may help identify the timer when debugging */
//            .name = "flash",
//            .skip_unhandled_events = false,
//
//    };

//    ESP_ERROR_CHECK(esp_timer_create(&flash_timer_args, &flash_timer));
//    esp_timer_start_periodic(flash_timer, 1000000);
}
//
//DateTimePage::~DateTimePage() {
//    esp_timer_delete(flash_timer);
//}


void DateTimePage::save_time() {
    tm timeinfo{};
    timeinfo.tm_sec = 0;
    timeinfo.tm_min = (*time % (SecondsInAnHour))/(SecondsInAMinute);
    timeinfo.tm_hour = *time/(SecondsInAnHour);
    timeinfo.tm_year = static_cast<int>(date->year + 100);
    timeinfo.tm_mon = static_cast<int>(date->month) - 1;
    timeinfo.tm_mday = static_cast<int>(date->day);

    time_t t = mktime(&timeinfo);
    settings::set_time(t);

    pop_page();
}
