//
// Created by rgray on 17/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_EDITJOBSPAGE_H
#define IRRIGATION_CONTROLLER_EDITJOBSPAGE_H


#include <memory>
#include "OptionsPage.h"
#include "Job.h"

class EditJobsPage : public OptionsPage {
public:
    explicit EditJobsPage(i2c_lcd1602_info_t * _lcd_info);
private:
    void navigate_to_edit_schedule_page(const std::shared_ptr<Job>& job);
    void navigate_to_edit_schedule_page();
    std::vector<std::shared_ptr<Job>> jobs;

    void schedule_updated();

    void setOptions();

    void schedule_deleted();
    void schedule_saved(std::shared_ptr<Job> job);
    void schedule_added(std::shared_ptr<Job> job);
};


#endif //IRRIGATION_CONTROLLER_EDITJOBSPAGE_H
