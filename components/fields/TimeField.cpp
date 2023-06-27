//
// Created by rgray on 18/06/2023.
//

#include "TimeField.h"
#include <sstream>

void TimeField::valueUp() {
    switch (get_editing_index()) {
        case 0: //hour
            hour += 1;

            if (hour >= 24) {
                hour -= 24;
            }
            break;
        case 1: //minute
            minute += 1;

            if (minute >= 60) {
                minute -= 60;
            }
            break;
        default:
            return;
    }

    *getTime() = hour * (SecondsInAnHour) + minute * (SecondsInAMinute);

    Field::valueUp();
}

void TimeField::valueDown() {
    switch (get_editing_index()) {
        case 0: //hour
            if (hour == 0) {
                hour = 23;
            } else {
                hour -= 1;
            }
            break;
        case 1: //minute
            if (minute == 0) {
                minute = 59;
            } else {
                minute -= 1;
            }
            break;
        default:
            return;
    }

    *getTime() = hour * (SecondsInAnHour) + minute * (SecondsInAMinute);

    Field::valueDown();
}

std::string TimeField::toString() {
    std::ostringstream str;
    if (get_editing_index() != 0 || isEditingVisible()) {
        if (hour < 10) {
            str << "0";
        }
        str << hour;
    } else {
        str << "  ";
    }

    str << ":";

    if (get_editing_index() != 1 || isEditingVisible()) {
        if (minute < 10) {
            str << "0";
        }
        str << minute;
    } else {
        str << "  ";
    }

    return str.str();
}

std::shared_ptr<unsigned int> TimeField::getTime() {
    return std::static_pointer_cast<unsigned int>(getValue());
}
