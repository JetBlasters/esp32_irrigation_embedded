//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_OPTION_H
#define IRRIGATION_CONTROLLER_OPTION_H


#include <string>

class Option {
public:
    Option() = default;
    virtual bool handleBack();
    virtual bool handleSelect();
    virtual bool handleUp();
    virtual bool handleDown();
    virtual std::string toString() = 0;
};


#endif //IRRIGATION_CONTROLLER_OPTION_H
