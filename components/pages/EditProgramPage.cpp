//
// Created by rgray on 23/06/2023.
//

#include "include/EditProgramPage.h"
#include "NavigationManager.h"
#include "DurationField.h"
#include "FieldOption.h"
#include "ShortField.h"
#include "FunctionalOption.h"

#include <utility>

EditProgramPage::EditProgramPage(i2c_lcd1602_info_t *lcd_info, Job::StationProgram program,
                                 function<void(Job::StationProgram)> saveProgramFunc) : OptionsPage(lcd_info),
                                                                                        saveProgramFunc(std::move(saveProgramFunc)){
    duration = make_shared<unsigned short>(program.duration);
    startDelay = make_shared<unsigned short>(program.startDelay);
    stationNumber = make_shared<unsigned short>(program.station);

    add_option(make_shared<fieldOption>("Station", make_unique<ShortField>(stationNumber, 1, 8)));
    add_option(make_shared<fieldOption>("Waits", make_unique<DurationField>(startDelay, 0, 6 * SecondsInAnHour)));
    add_option(make_shared<fieldOption>("Duratiom", make_unique<DurationField>(duration, 0, 6 * SecondsInAnHour)));
    add_option(make_shared<functionalOption>("Done...", [this] { saveProgram(); }));
}

void EditProgramPage::saveProgram() {
    saveProgramFunc({*stationNumber, *startDelay, *duration});
    pop_page();
}
