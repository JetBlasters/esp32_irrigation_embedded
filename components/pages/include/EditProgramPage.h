//
// Created by rgray on 23/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_EDITPROGRAMPAGE_H
#define IRRIGATION_CONTROLLER_EDITPROGRAMPAGE_H


#include "OptionsPage.h"

class EditProgramPage : public OptionsPage {
public:
    EditProgramPage(i2c_lcd1602_info_t* lcd_info, Job::StationProgram program,
                    function<void(Job::StationProgram)> saveRunFunc);
private:
    void saveProgram();
    function<void(Job::StationProgram)> saveProgramFunc;
    std::shared_ptr<unsigned short> duration;
    std::shared_ptr<unsigned short> startDelay;
    std::shared_ptr<unsigned short> stationNumber;
};


#endif //IRRIGATION_CONTROLLER_EDITPROGRAMPAGE_H
