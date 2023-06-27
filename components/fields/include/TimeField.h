//
// Created by rgray on 18/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_TIMEFIELD_H
#define IRRIGATION_CONTROLLER_TIMEFIELD_H

#include <utility>

#include "Field.h"

class TimeField : public Field {
public:
    explicit TimeField(std::shared_ptr<unsigned int> time)
    : Field(std::move(time), 2) {
        hour = *getTime() / (SecondsInAnHour);
        minute = (*getTime() % (SecondsInAnHour)) / (SecondsInAMinute);
    }

    std::string toString() override;
    void valueUp() override;
    void valueDown() override;
    std::shared_ptr<unsigned int> getTime();
private:
    short hour = 0;
    short minute = 0;
};


#endif //IRRIGATION_CONTROLLER_TIMEFIELD_H
