//
// Created by rgray on 18/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_FIELD_H
#define IRRIGATION_CONTROLLER_FIELD_H

#include <memory>
#include <functional>
#include <utility>
#include "settings.h"

// in milliseconds
#define FLASH_PERIOD 750

class Field {
public:
    explicit Field(std::shared_ptr<void> value, unsigned short editCount) : value(std::move(value)), editCount(editCount) {};

    std::shared_ptr<void> getValue();

    virtual void nextEdit();
    virtual void previousEdit();
    virtual void valueUp();
    virtual void valueDown();

    [[nodiscard]] bool isEditing() const;

    virtual std::string toString() = 0;
protected:
    bool isEditingVisible();
    void setEditCount(unsigned short count);
    unsigned short getEditCount();
    [[nodiscard]] short get_editing_index() const;
    void resetFlash();
    void setFlash();
private:
    long long lastFlash = 0;
    bool isEditing_ = false;
    std::shared_ptr<void> value;
    unsigned short editCount;
    short editIndex = 0;
    bool editingVisible = false;
};


#endif //IRRIGATION_CONTROLLER_FIELD_H
