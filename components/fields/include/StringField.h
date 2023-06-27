//
// Created by rgray on 23/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_STRINGFIELD_H
#define IRRIGATION_CONTROLLER_STRINGFIELD_H


#include "Field.h"

class StringField : public Field {
public:
    explicit StringField(std::shared_ptr<std::string> str) : Field(std::move(str), 1){
        setEditCount(getString()->size() + 1);
    }

    std::string toString() override;
    void valueDown() override;
    void valueUp() override;
    std::shared_ptr<std::string> getString();
private:
    static constexpr std::array<char,37> characters = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S',
                                          'T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9',' '};
};




#endif //IRRIGATION_CONTROLLER_STRINGFIELD_H
