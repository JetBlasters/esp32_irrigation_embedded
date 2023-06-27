//
// Created by rgray on 17/06/2023.
//

#include "EditJobsPage.h"
#include "settings.h"
#include "EditJobPage.h"
#include "NavigationManager.h"
#include "FunctionalOption.h"
#include "ScheduleOption.h"
#include <sstream>
#include <utility>

using namespace std;

EditJobsPage::EditJobsPage(i2c_lcd1602_info_t * _lcd_info) : OptionsPage(_lcd_info){
    //filter = [](schedule s) { return true; };
    setOptions();
}

//EditJobsPage::EditJobsPage(i2c_lcd1602_info_t *_lcd_info, schedule::DayOfWeek day) : OptionsPage(_lcd_info) {
//    esp_err_t err = settings::get_schedules(&schedules);
//    if (err != ERR_OK) {
//        printf("Error reading: %d\n", err);
//        return;
//    }
//
//    defaultDay = day;
//    filter = [day](schedule s) { return s.getDay() == day; };
//    setOptions(filter);
//}
//
//EditJobsPage::EditJobsPage(i2c_lcd1602_info_t *_lcd_info, unsigned short station) : OptionsPage(_lcd_info) {
//    esp_err_t err = settings::get_schedules(&schedules);
//    if (err != ERR_OK) {
//        printf("Error reading: %d\n", err);
//        return;
//    }
//
//    defaultStation = station;
//    filter = [station](schedule s) { return s.getStation() == station; };
//    setOptions(filter);
//}

void EditJobsPage::setOptions() {
    esp_err_t err = settings::retrieve_jobs(&jobs);
    if (err != ERR_OK) {
        printf("Error reading: %d\n", err);
        return;
    }

    reset_options();

    for (const std::shared_ptr<Job>& job : jobs) {
        auto jobCopy = make_shared<Job>(job->deepCopy());
            add_option(std::make_shared<ScheduleOption>(jobCopy,
            [this](const std::shared_ptr<Job>& job) {
                        navigate_to_edit_schedule_page(job);
            }));
    }

    add_option(std::make_shared<functionalOption>("Add job...", [this] {
        navigate_to_edit_schedule_page();
    }));
}

void EditJobsPage::navigate_to_edit_schedule_page(const std::shared_ptr<Job>& job) {
    auto jobCopy = make_shared<Job>(job->deepCopy());
    push_page(std::make_shared<EditJobPage>(lcd_info, job,
                                            [this](std::shared_ptr<Job> job)
                                                   { schedule_saved(std::move(job)); },
                                            [this] { schedule_deleted(); }));
}

void EditJobsPage::navigate_to_edit_schedule_page() {

    push_page(std::make_shared<EditJobPage>(lcd_info,
                                            std::make_shared<Job>("Job 1",
                                                                        vector<Job::StationProgram>(),
                                                                        vector<Job::Run>()),
                                            [this](std::shared_ptr<Job> job) {
                                                      schedule_added(std::move(job));
                                                  }, nullptr));
}

void EditJobsPage::schedule_updated() {
    // resets the options
    setOptions();
    OptionsPage::display_page();
}

void EditJobsPage::schedule_saved(std::shared_ptr<Job> job) {
    // saves the new schedule
    settings::save_job(job);

    jobs[get_selection()] = std::move(job);

    display_option(get_selection());
}

void EditJobsPage::schedule_deleted() {
    std::shared_ptr<ScheduleOption> scheduleOption = std::static_pointer_cast<ScheduleOption>(get_current_option());
    std::shared_ptr<Job> job = scheduleOption->getJob();

    // saves the new schedule
    settings::delete_job(job);

    // resets the options
    setOptions();
    OptionsPage::display_page();
}

void EditJobsPage::schedule_added(std::shared_ptr<Job> job) {
    // saves the new schedule
    settings::save_job(job);

    setOptions();
    OptionsPage::display_page();
}
