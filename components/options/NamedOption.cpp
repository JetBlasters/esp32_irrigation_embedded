//
// Created by rgray on 19/06/2023.
//

#include "include/NamedOption.h"

#include <utility>

std::string NamedOption::getName() {
    return name;
}

void NamedOption::setName(std::string newName) {
    name = std::move(newName);
}

std::string NamedOption::toString() {
    return name;
}
