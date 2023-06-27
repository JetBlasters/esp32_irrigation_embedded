//
// Created by rgray on 23/06/2023.
//

#include "StringField.h"

std::string StringField::toString() {
    if (!isEditing() || get_editing_index() > getString()->size()) {
        return (*getString());
    }

    string stringCopy = *getString();
    if (get_editing_index() == getString()->size()) {
        stringCopy += '.';
    }

    if (!isEditingVisible() && stringCopy[get_editing_index()] == ' ') {
        stringCopy[get_editing_index()] = '_';
    } else if (!isEditingVisible()) {
        stringCopy[get_editing_index()] = ' ';
    }

    return stringCopy;
}

void StringField::valueDown() {
    // increases the size if end of string.
    if (get_editing_index() >= getString()->size()) {
        *getString() += characters.back();
        setEditCount(getEditCount() + 1);
        Field::valueDown();
        return;
    }

    auto it = std::find(characters.begin(), characters.end(), (*getString())[get_editing_index()]);

    if (it != characters.end()) {
        int index = it - characters.begin();
        if (index == 0 && get_editing_index() >= getString()->size() - 1) {
            // removes the last element
            getString()->pop_back();
            setEditCount(getEditCount() - 1);
        } else if (index == 0) {
            (*getString())[get_editing_index()] = characters.back();
        } else {
            (*getString())[get_editing_index()] = characters[index - 1];
        }
    } else {
        // not a valid character
        (*getString())[get_editing_index()] = characters.back();
    }

    Field::valueDown();
}

void StringField::valueUp() {
    // increases the size if end of string.
    if (get_editing_index() >= getString()->size()) {
        *getString() += characters.front();
        setEditCount(getEditCount() + 1);
        Field::valueUp();
        return;
    }

    auto it = std::find(characters.begin(), characters.end(), (*getString())[get_editing_index()]);

    if (it != characters.end()) {
        int index = it - characters.begin();
        if (index == characters.size() - 1 && get_editing_index() >= getString()->size() - 1) {
            // removes the last element
            getString()->pop_back();
            setEditCount(getEditCount() + 1);
        } else if (index == characters.size() - 1) {
            (*getString())[get_editing_index()] = characters.front();
        } else {
            (*getString())[get_editing_index()] = characters[index + 1];
        }
    } else {
        // not a valid character
        (*getString())[get_editing_index()] = characters.front();
    }

    Field::valueUp();
}

std::shared_ptr<std::string> StringField::getString() {
    return std::static_pointer_cast<std::string>(getValue());
}
