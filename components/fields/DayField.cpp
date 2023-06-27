//
// Created by rgray on 19/06/2023.
//

#include "include/DayField.h"

std::string DayField::toString() {
    if (isEditingVisible()) {
        return Job::dayOfWeekString(*getDay());
    }

    return "";
}

void DayField::valueUp() {
    switch (*getDay()) {
        case Job::Monday:
            *getDay() = Job::Tuesday;
            break;
        case Job::Tuesday:
            *getDay() = Job::Wednesday;
            break;
        case Job::Wednesday:
            *getDay() = Job::Thursday;
            break;
        case Job::Thursday:
            *getDay() = Job::Friday;
            break;
        case Job::Friday:
            *getDay() = Job::Saturday;
            break;
        case Job::Saturday:
            *getDay() = Job::Sunday;
            break;
        case Job::Sunday:
            *getDay() = Job::Monday;
            break;
    }

    Field::valueUp();
}

void DayField::valueDown() {
    switch (*getDay()) {
        case Job::Monday:
            *getDay() = Job::Sunday;
            break;
        case Job::Tuesday:
            *getDay() = Job::Monday;
            break;
        case Job::Wednesday:
            *getDay() = Job::Tuesday;
            break;
        case Job::Thursday:
            *getDay() = Job::Wednesday;
            break;
        case Job::Friday:
            *getDay() = Job::Thursday;
            break;
        case Job::Saturday:
            *getDay() = Job::Friday;
            break;
        case Job::Sunday:
            *getDay() = Job::Saturday;
            break;
    }

    Field::valueDown();
}

std::shared_ptr<Job::DayOfWeek> DayField::getDay() {
    return std::static_pointer_cast<Job::DayOfWeek>(getValue());
}
