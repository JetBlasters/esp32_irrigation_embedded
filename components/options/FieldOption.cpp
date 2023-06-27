//
// Created by rgray on 19/06/2023.
//

#include <sstream>
#include "include/FieldOption.h"

bool fieldOption::handleSelect() {
    _field->nextEdit();
    return true;
}

bool fieldOption::handleBack() {
    if (_field->isEditing()) {
        _field->previousEdit();
        return true;
    }

    return false;
}

bool fieldOption::handleUp() {
    if (_field->isEditing()) {
        _field->valueUp();
        return true;
    }

    return false;
}

bool fieldOption::handleDown() {
    if (_field->isEditing()) {
        _field->valueDown();
        return true;
    }

    return false;
}

std::string fieldOption::toString() {
    std::ostringstream str;

    str << NamedOption::toString() << " - " << _field->toString();

    return str.str();
}