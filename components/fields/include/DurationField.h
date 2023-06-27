//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_DURATIONFIELD_H
#define IRRIGATION_CONTROLLER_DURATIONFIELD_H


#include "Field.h"

class DurationField : public Field {
public:
    DurationField(const std::shared_ptr<unsigned short>& value, unsigned short min, unsigned short max)
            : Field(value, 1), max(max), min(min) {};

    std::string toString() override;
    void valueUp() override;
    void valueDown() override;
    std::shared_ptr<unsigned short> getDuration();
private:
    unsigned short max;
    unsigned short min;
};


#endif //IRRIGATION_CONTROLLER_DURATIONFIELD_H
