//
// Created by rgray on 19/06/2023.
//

#include "include/ShortField.h"

void ShortField::valueUp() {
    if (*getShort() == max) {
        *getShort() = min;
    } else {
        (*getShort())++;
    }

    Field::valueUp();
}

void ShortField::valueDown() {
    if (*getShort() == min) {
        *getShort() = max;
    } else {
        (*getShort())--;
    }

    Field::valueDown();
}

std::shared_ptr<unsigned short> ShortField::getShort() {
    return std::static_pointer_cast<unsigned short>(getValue());
}

std::string ShortField::toString() {
    if (isEditingVisible()) {
        return std::to_string(*getShort());
    } else {
        return "";
    }
}