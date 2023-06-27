//
// Created by rgray on 23/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_EDITPROGRAMSPAGE_H
#define IRRIGATION_CONTROLLER_EDITPROGRAMSPAGE_H

#include "OptionsPage.h"

using namespace std;

class EditProgramsPage : public OptionsPage {
public:
    EditProgramsPage(i2c_lcd1602_info_t* lcd_info, std::shared_ptr<Job> job);
private:
    std::shared_ptr<Job> job;
    void update_options();
    void add_program();
    void edit_program(Job::StationProgram program);
    void program_added(Job::StationProgram program);
    void program_edited(Job::StationProgram program);
};


#endif //IRRIGATION_CONTROLLER_EDITPROGRAMSPAGE_H
