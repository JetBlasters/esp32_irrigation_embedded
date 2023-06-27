//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_FILTERSCHEDULESPAGE_H
#define IRRIGATION_CONTROLLER_FILTERSCHEDULESPAGE_H


#include "OptionsPage.h"

class FilterSchedulesPage : public OptionsPage {
public:
    explicit FilterSchedulesPage(i2c_lcd1602_info_t* _lcd_info);
};


#endif //IRRIGATION_CONTROLLER_FILTERSCHEDULESPAGE_H
