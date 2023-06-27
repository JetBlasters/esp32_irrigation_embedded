//
// Created by rgray on 23/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_EDITRUNSPAGE_H
#define IRRIGATION_CONTROLLER_EDITRUNSPAGE_H


#include "OptionsPage.h"

using namespace std;

class EditRunsPage : public OptionsPage {
public:
    EditRunsPage(i2c_lcd1602_info_t* lcd_info, std::shared_ptr<Job> job);
private:
    std::shared_ptr<Job> job;
    void update_options();
    void add_run();
    void edit_run(Job::Run run);
    void run_added(Job::Run run);
    void run_edited(Job::Run run);
};


#endif //IRRIGATION_CONTROLLER_EDITRUNSPAGE_H
