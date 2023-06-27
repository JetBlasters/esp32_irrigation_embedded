//
// Created by rgray on 7/02/2023.
//

#include "Page.h"

#ifndef IRRIGATION_CONTROLLER_MAIN_PAGE_H
#define IRRIGATION_CONTROLLER_MAIN_PAGE_H


class MainPage : public Page {
public:
    explicit MainPage(i2c_lcd1602_info_t * _lcd_info) : Page(_lcd_info) {}
    void display_page() override;
    void handle_back() override;
    void handle_select() override;
    void handle_left() override;
    void handle_right() override;
private:
    void navigate_to_settings();
};


#endif //IRRIGATION_CONTROLLER_MAIN_PAGE_H
