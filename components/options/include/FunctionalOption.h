//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_FUNCTIONALOPTION_H
#define IRRIGATION_CONTROLLER_FUNCTIONALOPTION_H

#include <string>
#include <functional>
#include "Option.h"
#include "NamedOption.h"

class functionalOption : public NamedOption {
public:
    functionalOption(std::string name, std::function<void()> function)
            : NamedOption(std::move(name)), function(std::move(function)) {}
    bool handleSelect() override;
private:
    std::function<void()> function;
};


#endif //IRRIGATION_CONTROLLER_FUNCTIONALOPTION_H
