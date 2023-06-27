//
// Created by rgray on 21/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_DATEFIELD_H
#define IRRIGATION_CONTROLLER_DATEFIELD_H

#include "Field.h"

typedef struct {
    unsigned short day;
    unsigned short month;
    unsigned short year;
} Date;

class DateField : public Field {
public:
    explicit DateField(std::shared_ptr<Date> date) : Field(std::move(date), 3) {}

    std::string toString() override;
    void valueDown() override;
    void valueUp() override;
    std::shared_ptr<Date> getDate();

    static bool is_leap(unsigned int y);

    void updateDayValue();

    int last_day_of_month();
};


#endif //IRRIGATION_CONTROLLER_DATEFIELD_H
