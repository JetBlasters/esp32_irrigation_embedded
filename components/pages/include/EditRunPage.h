//
// Created by rgray on 23/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_EDITRUNPAGE_H
#define IRRIGATION_CONTROLLER_EDITRUNPAGE_H


#include "OptionsPage.h"

using namespace std;

class EditRunPage : public OptionsPage {
public:
    EditRunPage(i2c_lcd1602_info_t* lcd_info, Job::Run run, function<void(Job::Run)> saveRunFunc);
private:
    void saveRun();
    function<void(Job::Run)> saveRunFunc;
    std::shared_ptr<unsigned int> time;
    std::shared_ptr<Job::DayOfWeek> day;
    std::shared_ptr<Job::WeeksRun> weeksRun;
};


#endif //IRRIGATION_CONTROLLER_EDITRUNPAGE_H
