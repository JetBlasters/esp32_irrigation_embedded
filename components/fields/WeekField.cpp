//
// Created by rgray on 19/06/2023.
//

#include <string>
#include "include/WeekField.h"

std::string WeekField::toString() {
    if (isEditingVisible()) {
        return Job::weeksRunString(*getWeek());
    }

    return "";
}

void WeekField::valueUp() {
    switch (*getWeek()) {
        case Job::WEEK1:
            *getWeek() = Job::WEEK2;
            break;
        case Job::WEEK2:
            *getWeek() = Job::BOTH;
            break;
        case Job::BOTH:
            *getWeek() = Job::WEEK1;
            break;
    }

    Field::valueUp();
}

void WeekField::valueDown() {
    switch (*getWeek()) {
        case Job::WEEK1:
            *getWeek() = Job::BOTH;
            break;
        case Job::WEEK2:
            *getWeek() = Job::WEEK1;
            break;
        case Job::BOTH:
            *getWeek() = Job::WEEK2;
            break;
    }

    Field::valueDown();
}

std::shared_ptr<Job::WeeksRun> WeekField::getWeek() {
    return std::static_pointer_cast<Job::WeeksRun>(getValue());
}