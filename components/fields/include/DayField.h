//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_DAYFIELD_H
#define IRRIGATION_CONTROLLER_DAYFIELD_H


#include "Field.h"

class DayField : public Field {
public:
    explicit DayField(std::shared_ptr<Job::DayOfWeek> day)
            : Field(std::move(day), 1) {}

    std::string toString() override;
    void valueUp() override;
    void valueDown() override;
    std::shared_ptr<Job::DayOfWeek> getDay();
};


#endif //IRRIGATION_CONTROLLER_DAYFIELD_H
