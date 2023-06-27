//
// Created by rgray on 6/02/2023.
//
#ifndef IRRIGATION_CONTROLLER_PAGE_H
#define IRRIGATION_CONTROLLER_PAGE_H

#include <string>
#include <functional>
#include "i2c-lcd1602.h"

class Page {
public:
    Page(i2c_lcd1602_info_t * _lcd_info);
    virtual void handle_select(void);
    virtual void handle_back(void);
    virtual void handle_left(void);
    virtual void handle_right(void);
    virtual void display_page(void);
    virtual void navigated_back();
    virtual void page_loop(void);
    virtual ~Page() = default;
protected:
    int count = 0;
    i2c_lcd1602_info_t * lcd_info;
};

typedef struct {
    std::function<void()> function;
    std::string pageName;
} navigation;


#endif //IRRIGATION_CONTROLLER_PAGE_H
