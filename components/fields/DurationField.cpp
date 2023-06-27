//
// Created by rgray on 19/06/2023.
//

#include <sstream>
#include "include/DurationField.h"

void DurationField::valueUp() {
    if (*getDuration() >= max) {
        *getDuration() = min;
    } else {
        (*getDuration()) += (SecondsInAMinute);
    }

    Field::valueUp();
}

void DurationField::valueDown() {
    if (*getDuration() <= min) {
        *getDuration() = max;
    } else {
        (*getDuration()) -= (SecondsInAMinute);
    }

    Field::valueDown();
}

std::shared_ptr<unsigned short> DurationField::getDuration() {
    return std::static_pointer_cast<unsigned short>(getValue());
}

std::string DurationField::toString() {
    std::ostringstream str;

    unsigned short minutes = (*getDuration() % (SecondsInAnHour)) / (SecondsInAMinute);
    unsigned short hours = (*getDuration()) / (SecondsInAnHour);

    printf("%d\n", hours);
    if (hours != 0) {
        str << hours << "h ";
    }

    if (isEditingVisible()) {
        str << minutes;
    } else {
        unsigned short digits = 0;
        do {
            digits++;
        } while (minutes /= 10);

        str << std::string(digits, ' ');
    }

    if (hours != 0) {
        str << "m";
    } else {
        str << " mins";
    }

    return str.str();
}