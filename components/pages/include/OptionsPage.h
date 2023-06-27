//
// Created by rgray on 17/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_OPTIONSPAGE_H
#define IRRIGATION_CONTROLLER_OPTIONSPAGE_H

#include <utility>
#include <vector>
#include "i2c-lcd1602.h"
#include "Page.h"
#include "Option.h"
#include "Field.h"
#include <map>

#define SCROLL_INTERVAL 1000
#define PAUSE_DELAY 3000

class OptionsPage : public Page {
public:
    explicit OptionsPage(i2c_lcd1602_info_t * _lcd_info) : Page(_lcd_info) {};
    void handle_select() override;
    void handle_back() override;
    void handle_left() override;
    void handle_right() override;
    void display_page() override;
    void page_loop() override;
    void display_option(short index);
    void display_option(short index, short scrollPosition);
protected:
    void add_option(std::shared_ptr<Option> option);
    void reset_options();
    std::shared_ptr<Option> get_current_option();
    short get_selection() const;
    short get_scrollPos() const;
    size_t getOptionsSize();
private:
    short selection = 0;
    short scrollPos = 0;
    std::map<short, std::string> lastString;
    std::vector<std::shared_ptr<Option>> options;
    long long lastScrollTime = 0;
    std::map<short, short> scrollIndex;
    std::map<short, long long> pauseUntil;
};

#endif //IRRIGATION_CONTROLLER_OPTIONSPAGE_H
