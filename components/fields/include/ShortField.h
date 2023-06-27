//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_SHORTFIELD_H
#define IRRIGATION_CONTROLLER_SHORTFIELD_H

#include <memory>
#include "Field.h"

class ShortField : public Field {
public:
    ShortField(const std::shared_ptr<unsigned short>& value, unsigned short min, unsigned short max)
    : Field(value, 1), max(max), min(min) {};

    std::string toString() override;
    void valueUp() override;
    void valueDown() override;
    std::shared_ptr<unsigned short> getShort();
private:
    unsigned short max;
    unsigned short min;
};


#endif //IRRIGATION_CONTROLLER_SHORTFIELD_H
