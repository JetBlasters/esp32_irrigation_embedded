//
// Created by rgray on 21/06/2023.
//

#include <sstream>
#include "DateField.h"

std::string DateField::toString() {
    std::ostringstream str;

    if (get_editing_index() != 0 || isEditingVisible()) {
        if (getDate()->day<10) {
            str << "0";
        }
        str << getDate()->day;
    } else {
        str << "  ";
    }
    str << "/";
    if (get_editing_index() != 1 || isEditingVisible()) {
        if (getDate()->month<10) {
            str << "0";
        }
        str << getDate()->month;
    } else {
        str << "  ";
    }
    str << "/";
    if (get_editing_index() != 2 || isEditingVisible()) {
        if (getDate()->year<10) {
            str << "0";
        }
        str << getDate()->year;
    } else {
        str << "  ";
    }

    return str.str();
}

void DateField::valueDown() {
    switch (get_editing_index()) {
        case 0: // day
            if (getDate()->day <= 1) {
                getDate()->day = last_day_of_month();
                break;
            }
            getDate()->day--;
            break;
        case 1: // month
            if (getDate()->month <= 1) {
                getDate()->month = 12;
                updateDayValue();
                break;
            }
            getDate()->month--;
            updateDayValue();
            break;
        case 2: // year
            if (getDate()->year == 0) {
                getDate()->year=99;
                updateDayValue();
                break;
            }
            getDate()->year--;
            updateDayValue();
            break;
    }

    Field::valueDown();
}

void DateField::updateDayValue() {
    if (getDate()->day > last_day_of_month()) {
        getDate()->day = last_day_of_month();
    }
}


void DateField::valueUp() {switch (get_editing_index()) {
        case 0: // day
            if (getDate()->day >= last_day_of_month()) {
                getDate()->day = 1;
                break;
            }
            getDate()->day++;
            break;
        case 1: // month
            if (getDate()->month >= 12) {
                getDate()->month = 1;
                updateDayValue();
                break;
            }
            getDate()->month++;
            updateDayValue();
            break;
        case 2: // year
            if (getDate()->year == 99) {
                getDate()->year = 0;
                updateDayValue();
                break;
            }
            getDate()->year++;
            updateDayValue();
            break;
    }

    Field::valueUp();
}

std::shared_ptr<Date> DateField::getDate() {
    return std::static_pointer_cast<Date>(getValue());
}



bool DateField::is_leap(unsigned y)
{
    return  y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}

int DateField::last_day_of_month()
{
    if (getDate()->month != 2 || !is_leap(getDate()->year)) {
        int a[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return a[getDate()->month - 1];
    } else {
        return 29u;
    }
}
