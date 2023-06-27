//
// Created by rgray on 23/06/2023.
//

#include "include/EditRunsPage.h"
#include "FunctionalOption.h"
#include "NavigationManager.h"
#include "EditRunPage.h"

#include <utility>

using namespace std;

EditRunsPage::EditRunsPage(i2c_lcd1602_info_t* lcd_info, std::shared_ptr<Job> job)
                           : OptionsPage(lcd_info), job(std::move(job)) {
    update_options();
}

void EditRunsPage::update_options() {
    reset_options();

    for (Job::Run run : job->getRuns()) {
        add_option(make_shared<functionalOption>(job->runToString(run), [this, run] { edit_run(run); }));
    }

    add_option(make_shared<functionalOption>("Add run...", [this] { add_run(); }));
}

void EditRunsPage::add_run() {
    Job::Run newRun = {6 * SecondsInAnHour, Job::Monday, Job::BOTH};
    push_page(make_shared<EditRunPage>(lcd_info, newRun,
                                       [this](Job::Run run) { run_added(run); }));
}

void EditRunsPage::edit_run(Job::Run editingRun) {
    push_page(make_shared<EditRunPage>(lcd_info, editingRun,
                                       [this](Job::Run run) { run_edited(run); }));
}

void EditRunsPage::run_edited(Job::Run run) {
    job->updateRun(get_selection(), run);
    update_options();
}

void EditRunsPage::run_added(Job::Run run) {
    job->addRun(run);
    update_options();
}

