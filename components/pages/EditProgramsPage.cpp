//
// Created by rgray on 23/06/2023.
//

#include "EditProgramsPage.h"
#include "FunctionalOption.h"
#include "EditProgramPage.h"
#include "NavigationManager.h"

using namespace std;

EditProgramsPage::EditProgramsPage(i2c_lcd1602_info_t* lcd_info, std::shared_ptr<Job> job)
        : OptionsPage(lcd_info), job(std::move(job)) {
    update_options();
}

void EditProgramsPage::update_options() {
    reset_options();

    for (Job::StationProgram program : job->getStationPrograms()) {
        add_option(make_shared<functionalOption>(job->stationProgramToString(program),
                                                 [this, program] { edit_program(program); }));
    }

    add_option(make_shared<functionalOption>("Add station...", [this] { add_program(); }));
}

void EditProgramsPage::add_program() {
    Job::StationProgram newRun = {1, 0, 30*SecondsInAMinute};
    push_page(make_shared<EditProgramPage>(lcd_info, newRun,
                                       [this](Job::StationProgram program) { program_added(program); }));
}

void EditProgramsPage::edit_program(Job::StationProgram editingProgram) {
    push_page(make_shared<EditProgramPage>(lcd_info, editingProgram,
                                       [this](Job::StationProgram program) { program_edited(program); }));
}

void EditProgramsPage::program_added(Job::StationProgram program) {
    job->addStationProgram(program);
    update_options();
}

void EditProgramsPage::program_edited(Job::StationProgram program) {
    job->updateStationProgram(get_selection(), program);
    update_options();
}