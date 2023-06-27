//
// Created by rgray on 17/06/2023.
//

#include "include/OptionsPage.h"

#include <utility>
#include <sstream>
#include <esp_timer.h>
#include "Option.h"

void OptionsPage::display_page() {
    lastScrollTime = esp_timer_get_time();
    i2c_lcd1602_clear(lcd_info);
    for (short i = 0; (i + scrollPos) < options.size() && i < 4; i ++) {
        display_option(i + scrollPos);
    }
}

void OptionsPage::page_loop() {
    if (get_current_option()->toString() != lastString[get_selection()]) {
        display_option(selection);
    }

    long long currentTime = esp_timer_get_time();

    if (lastScrollTime + (SCROLL_INTERVAL * 1000) <= currentTime) {
        for (short i = 0; (i + scrollPos) < options.size() && i < 4; i ++) {
            short index = i + scrollPos;

            std::string output = lastString[index];
            if (output.length() > 19 && pauseUntil[index] < currentTime) {
                // needs to scroll
                if (output.length() - scrollIndex[index] <= 19) {
                    scrollIndex[index] = 0;
                    pauseUntil[index] = currentTime + (PAUSE_DELAY * 1000);
                } else {
                    scrollIndex[index]++;

                    if (output.length() - scrollIndex[index] <= 19) {
                        pauseUntil[index] = currentTime + (PAUSE_DELAY * 1000);
                    }

                }
                display_option(index, scrollIndex[index]);
            }
        }
        lastScrollTime = currentTime;
    }

}

std::shared_ptr<Option> OptionsPage::get_current_option() {
    return options.at(selection);
}

void OptionsPage::handle_right() {
    // if the Option suppresses input, return.
    if (get_current_option()->handleDown()) {
        display_option(selection);
        return;
    }

    selection++;
    // scroll if needed
    if (selection >= scrollPos + 4) {
        scrollPos++;
    }
    // wrap if out of range
    if (selection >= options.size()) {
        selection = 0;
        scrollPos = 0;
    }
    display_page();
}
void OptionsPage::handle_left() {
    // if the Option suppresses input, return.
    if (get_current_option()->handleUp()) {
        display_option(selection);
        return;
    }

    selection--;
    // scroll if needed
    if (selection < scrollPos && options.size() > 4) {
        scrollPos--;
    }
    // wrap if out of range
    if (selection < 0) {
        selection = options.size() - 1;
        if (options.size() > 4) {
            scrollPos = options.size() - 4;
        }
    }
    display_page();
}

void OptionsPage::handle_back() {
    if (get_current_option()->handleBack()) {
        display_option(selection);
        return;
    }

    Page::handle_back();
}

void OptionsPage::handle_select() {
    if (get_current_option()->handleSelect()) {
        printf("Display Option\n");
        display_option(selection);
    }
}

void OptionsPage::add_option(std::shared_ptr<Option> opt) {
    options.push_back(std::move(opt));
}

short OptionsPage::get_scrollPos() const {
    return scrollPos;
}

short OptionsPage::get_selection() const {
    return selection;
}

size_t OptionsPage::getOptionsSize() {
    return options.size();
}

void OptionsPage::display_option(short index) {
    std::string optionsString = options.at(index)->toString();
    lastString[index] = optionsString;

    scrollIndex[index] = 0;
    pauseUntil[index] = esp_timer_get_time() + (PAUSE_DELAY * 1000);
    display_option(index, 0);
}


void OptionsPage::display_option(short index, short scrollPosition) {
    // not being displayed
    if (index < (scrollPos) || index >= (scrollPos + 4)) {
        return;
    }

    i2c_lcd1602_move_cursor(lcd_info, 0,index - scrollPos);

    std::ostringstream str;

    if (selection == index) {
        str << ">";
    } else {
        str << " ";
    }

    std::string optionsString = lastString[index];
    // trims if too long.
    optionsString = optionsString.substr(scrollPosition, 19);

    str << optionsString;
    str << std::string(20 - str.str().length(), ' ');
    i2c_lcd1602_write_string(lcd_info, str.str().c_str());
}

void OptionsPage::reset_options() {
    options.clear();
    lastString.clear();
}




