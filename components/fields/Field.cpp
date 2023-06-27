//
// Created by rgray on 18/06/2023.
//

#include <esp_timer.h>
#include "include/Field.h"
#include "../settings/include/settings.h"


void Field::nextEdit() {
    if (isEditing_) {
        editIndex++;
        if (editIndex >= editCount) {
            isEditing_ = false;
            resetFlash();
            return;
        }
    } else {
        isEditing_ = true;
        editIndex = 0;
    }

    setFlash();
}

void Field::previousEdit() {
    if (isEditing_) {
        editIndex--;
        if (editIndex < 0) {
            isEditing_ = false;
            resetFlash();
            return;
        }
    } else {
        isEditing_ = true;
        editIndex = editCount - 1;
    }

    setFlash();
}

void Field::resetFlash() {
    lastFlash = esp_timer_get_time();;
    editingVisible = true;
}

void Field::setFlash() {
    lastFlash = esp_timer_get_time();;
    editingVisible = false;
}

bool Field::isEditingVisible() {
    if (!isEditing_) {
        return true;
    }

    long long currentTime = esp_timer_get_time();

    // divide by 1000 since difftime returns number of seconds.
    if ((currentTime - lastFlash)/1000 >= FLASH_PERIOD) {
        editingVisible = !editingVisible;
        lastFlash = currentTime;
    }

    return editingVisible;
}

std::shared_ptr<void> Field::getValue() {
    return value;
}

void Field::valueUp() {
    resetFlash();
}

void Field::valueDown() {
    resetFlash();
}

short Field::get_editing_index() const {
    return editIndex;
}

bool Field::isEditing() const {
    return isEditing_;
}

void Field::setEditCount(unsigned short count) {
    editCount = count;
}

unsigned short Field::getEditCount() {
    return editCount;
}
