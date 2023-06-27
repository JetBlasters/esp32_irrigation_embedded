//
// Created by rgray on 6/02/2023.
//

#include <vector>
#include "driver/gpio.h"

#ifndef IRRIGATION_CONTROLLER_SHIFT_REGISTER_H
#define IRRIGATION_CONTROLLER_SHIFT_REGISTER_H
class shift_register {
public:
    shift_register(gpio_num_t ser, gpio_num_t rclk, gpio_num_t srclk);
    void add_station(int station);
    void remove_station(int station);
    void update_output();
private:
    gpio_num_t ser;
    gpio_num_t rclk;
    gpio_num_t srclk;
    std::vector<int> stationsEnabled;
    void output(int8_t output);
};
#endif //IRRIGATION_CONTROLLER_SHIFT_REGISTER_H
