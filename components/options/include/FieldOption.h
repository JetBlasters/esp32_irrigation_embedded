//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_FIELDOPTION_H
#define IRRIGATION_CONTROLLER_FIELDOPTION_H


#include <string>
#include <memory>
#include "Field.h"
#include "NamedOption.h"

class fieldOption : public NamedOption {
public:
    fieldOption(std::string name, std::unique_ptr<Field> _field)
            : NamedOption(std::move(name)), _field(std::move(_field)) {}
    bool handleBack() override;
    bool handleSelect() override;
    bool handleUp() override;
    bool handleDown() override;
    std::string toString() override;
protected:
    std::unique_ptr<Field> _field;
};


#endif //IRRIGATION_CONTROLLER_FIELDOPTION_H
