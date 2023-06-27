//
// Created by rgray on 17/06/2023.
//

#include "EditJobPage.h"
#include <functional>
#include "NavigationManager.h"
#include "TimeField.h"
#include "FieldOption.h"
#include "FunctionalOption.h"
#include "ShortField.h"
#include "DurationField.h"
#include "DayField.h"
#include "WeekField.h"
#include "StringField.h"
#include "EditRunsPage.h"
#include "EditProgramsPage.h"
#include <memory>
#include <utility>

using namespace std;

EditJobPage::EditJobPage(i2c_lcd1602_info_t *_lcd_info, std::shared_ptr<Job> job_,
                         std::function<void(std::shared_ptr<Job>)> saveFunc_,
                         std::function<void()> deleteFunc_)
                                       : OptionsPage(_lcd_info),
                                         deleteFunc(std::move(deleteFunc_)),
                                         saveFunc(std::move(saveFunc_)),
                                         job(std::move(job_)) {

    name = std::make_shared<string>(job->getName());

    add_option(std::make_shared<fieldOption>("Name", std::make_unique<StringField>(name)));
    add_option(std::make_shared<functionalOption>("Edit program...",
                                                  [this] { push_page(std::make_shared<EditProgramsPage>(lcd_info, job)); }));
    add_option(std::make_shared<functionalOption>("Edit schedule...",
                                                  [this] { push_page(std::make_shared<EditRunsPage>(lcd_info, job)); }));
    add_option(std::make_shared<functionalOption>(
            "Save job...", [this] { saveJob(); }));
    if (deleteFunc != nullptr) {
        add_option(std::make_shared<functionalOption>(
                "Delete job...", [this] { deleteJob(); }));
    }
}

void EditJobPage::saveJob() {
    job->setName(*name);
    saveFunc(std::move(job));
    pop_page();
}

void EditJobPage::deleteJob() {
    deleteFunc();
    pop_page();
}
