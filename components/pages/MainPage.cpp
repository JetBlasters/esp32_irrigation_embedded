//
// Created by rgray on 7/02/2023.
//

#include "MainPage.h"
#include "NavigationManager.h"
#include "SettingsPage.h"

void MainPage::display_page() {
    i2c_lcd1602_clear(lcd_info);
    i2c_lcd1602_home(lcd_info);
    i2c_lcd1602_write_string(lcd_info, "Irrigation System");
    i2c_lcd1602_move_cursor(lcd_info, 0, 1);
    i2c_lcd1602_write_string(lcd_info, "Upcoming job...");
}

void MainPage::handle_back() {
    navigate_to_settings();
}

void MainPage::handle_select() {
    navigate_to_settings();
}

void MainPage::handle_left() {
    navigate_to_settings();
}

void MainPage::handle_right() {
    navigate_to_settings();
}

void MainPage::navigate_to_settings() {
    push_page(std::make_shared<SettingsPage>(lcd_info));

}
