//
// Created by rgray on 23/06/2023.
//

#include "include/EditRunPage.h"
#include "FieldOption.h"
#include "TimeField.h"
#include "DayField.h"
#include "WeekField.h"
#include "FunctionalOption.h"
#include "NavigationManager.h"

#include <utility>

EditRunPage::EditRunPage(i2c_lcd1602_info_t *lcd_info, Job::Run run, function<void(Job::Run)> saveRunFunc)
        : OptionsPage(lcd_info), saveRunFunc(std::move(saveRunFunc)) {
    time = make_shared<unsigned int>(run.time);
    day = make_shared<Job::DayOfWeek>(run.day);
    weeksRun = make_shared<Job::WeeksRun>(run.weeksRun);

    add_option(make_shared<fieldOption>("Time", make_unique<TimeField>(time)));
    add_option(make_shared<fieldOption>("Day", make_unique<DayField>(day)));
    add_option(make_shared<fieldOption>("Weeks", make_unique<WeekField>(weeksRun)));
    add_option(make_shared<functionalOption>("Done...", [this] { saveRun(); }));
}

void EditRunPage::saveRun() {
    saveRunFunc({*time, *day, *weeksRun});
    pop_page ();
}
