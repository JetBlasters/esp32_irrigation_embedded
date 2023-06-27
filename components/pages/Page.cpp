//
// Created by rgray on 6/02/2023.
//

#include <cstdlib>
#include "Page.h"
#include "NavigationManager.h"
#include "i2c-lcd1602.h"
#include "MainPage.h"

Page::Page(i2c_lcd1602_info_t *_lcd_info)  : lcd_info(_lcd_info){
}

void Page::handle_back() {
    pop_page();
}
void Page::handle_select() {
    push_page(std::make_shared<Page>(MainPage(lcd_info)));
    count--;
}
void Page::handle_left() {
    display_page();
}
void Page::handle_right() {
    display_page();
}

void Page::display_page() {
    i2c_lcd1602_clear(lcd_info);
    i2c_lcd1602_home(lcd_info);
    i2c_lcd1602_write_string(lcd_info, "Test ");
    char snum[5];
    i2c_lcd1602_write_string(lcd_info, itoa(count, snum, 10));
    count++;
}

void Page::page_loop() {

}

void Page::navigated_back() {

}

