//
// Created by rgray on 8/02/2023.
//

#ifndef IRRIGATION_CONTROLLER_SETTINGSPAGE_H
#define IRRIGATION_CONTROLLER_SETTINGSPAGE_H

#include <vector>
#include "OptionsPage.h"

class SettingsPage : public OptionsPage {
public:
    explicit SettingsPage(i2c_lcd1602_info_t * _lcd_info);
private:
    void navigate_to_date_time_page();
    void navigate_to_edit_schedules_page();
};


#endif //IRRIGATION_CONTROLLER_SETTINGSPAGE_H
