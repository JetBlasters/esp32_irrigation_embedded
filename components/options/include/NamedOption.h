//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_NAMEDOPTION_H
#define IRRIGATION_CONTROLLER_NAMEDOPTION_H


#include "Option.h"

class NamedOption : public Option {
public:
    explicit NamedOption(std::string name) : name(std::move(name)) {};
    std::string getName();
    void setName(std::string newName);
    std::string toString() override;
private:
    std::string name;
};


#endif //IRRIGATION_CONTROLLER_NAMEDOPTION_H
