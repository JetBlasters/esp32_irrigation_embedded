//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_WEEKFIELD_H
#define IRRIGATION_CONTROLLER_WEEKFIELD_H


#include "Field.h"

class WeekField : public Field {
public:
    explicit WeekField(const std::shared_ptr<Job::WeeksRun>& day)
    : Field(day, 1) {}

    std::string toString() override;
    void valueUp() override;
    void valueDown() override;
    std::shared_ptr<Job::WeeksRun> getWeek();
};


#endif //IRRIGATION_CONTROLLER_WEEKFIELD_H
