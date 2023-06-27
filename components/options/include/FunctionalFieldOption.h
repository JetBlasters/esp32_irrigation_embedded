//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_FUNCTIONALFIELDOPTION_H
#define IRRIGATION_CONTROLLER_FUNCTIONALFIELDOPTION_H


#include <string>
#include <utility>
#include "Field.h"
#include "FieldOption.h"

class FunctionalFieldOption : public fieldOption {
public:
    FunctionalFieldOption(std::string name, std::unique_ptr<Field> _field, std::function<void(std::shared_ptr<void>)> func)
            : fieldOption(std::move(name), std::move(_field)), func(std::move(func)) {}

    bool handleSelect() override;
private:
    std::function<void(std::shared_ptr<void>)> func;
};


#endif //IRRIGATION_CONTROLLER_FUNCTIONALFIELDOPTION_H
