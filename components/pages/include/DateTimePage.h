//
// Created by rgray on 8/02/2023.
//

#include "Page.h"
#include "esp_timer.h"
#include "OptionsPage.h"
#include "TimeField.h"
#include "DateField.h"

#ifndef IRRIGATION_CONTROLLER_DATE_TIME_PAGE_H
#define IRRIGATION_CONTROLLER_DATE_TIME_PAGE_H


class DateTimePage : public OptionsPage {
public:
    explicit DateTimePage(i2c_lcd1602_info_t * _lcd_info);
//    void page_loop() override;
//    static void timer_isr_handler(void* arg);
//    esp_timer_handle_t flash_timer;
private:
    void save_time();
    std::shared_ptr<unsigned int> time;
    std::shared_ptr<Date> date;
};


#endif //IRRIGATION_CONTROLLER_DATE_TIME_PAGE_H
