//
// Created by rgray on 6/02/2023.
//


#ifndef IRRIGATION_CONTROLLER_BUTTONHANDLER_H
#define IRRIGATION_CONTROLLER_BUTTONHANDLER_H
void add_button(gpio_num_t);
bool is_button_pressed(gpio_num_t gpioNum);
#endif //IRRIGATION_CONTROLLER_BUTTONHANDLER_H