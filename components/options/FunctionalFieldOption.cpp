//
// Created by rgray on 19/06/2023.
//

#include "include/FunctionalFieldOption.h"

bool FunctionalFieldOption::handleSelect() {
    bool before = _field->isEditing();
    bool blockInput = fieldOption::handleSelect();
    if (before && !_field->isEditing()) {
        func(_field->getValue());
        return false;
    }
    return blockInput;
}
