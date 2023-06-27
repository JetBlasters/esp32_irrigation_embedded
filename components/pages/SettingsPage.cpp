//
// Created by rgray on 8/02/2023.
//

#include "SettingsPage.h"
#include "NavigationManager.h"
#include "MainPage.h"
#include "DateTimePage.h"
#include <functional>
#include <memory>
#include "settings.h"
#include "EditJobsPage.h"
#include "FunctionalOption.h"
#include "FilterSchedulesPage.h"

SettingsPage::SettingsPage(i2c_lcd1602_info_t * _lcd_info) : OptionsPage(_lcd_info){
    add_option(std::make_unique<NamedOption>("Toggle stations"));
    add_option(std::make_unique<functionalOption>("Edit jobs",
                                                  [this] { navigate_to_edit_schedules_page(); }));
    add_option(std::make_unique<functionalOption>("Date & time",
                                                  [this] { navigate_to_date_time_page(); }));
}

void SettingsPage::navigate_to_date_time_page() {
    push_page(std::make_shared<DateTimePage>(lcd_info));
}

void SettingsPage::navigate_to_edit_schedules_page() {
    push_page(std::make_shared<FilterSchedulesPage>(lcd_info));
}
