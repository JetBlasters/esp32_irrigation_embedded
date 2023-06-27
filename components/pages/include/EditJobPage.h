//
// Created by rgray on 17/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_EDITJOBPAGE_H
#define IRRIGATION_CONTROLLER_EDITJOBPAGE_H


#include <memory>
#include "OptionsPage.h"

class EditJobPage : public OptionsPage {
public:
    EditJobPage(i2c_lcd1602_info_t *_lcd_info, std::shared_ptr<Job> job,
                std::function<void(std::shared_ptr<Job>)> saveFunc,
                std::function<void()> deleteFunc);
    void saveJob();
    void deleteJob();
private:
    std::function<void()> deleteFunc;
    std::function<void(std::shared_ptr<Job>)> saveFunc;
    shared_ptr<string> name;
    std::shared_ptr<Job> job;
};


#endif //IRRIGATION_CONTROLLER_EDITJOBPAGE_H
