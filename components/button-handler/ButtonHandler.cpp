//
// Created by rgray on 6/02/2023.
//
#include <string>
#include "sdkconfig.h"
#include "rom/uart.h"
#include "driver/gpio.h"
#include "ButtonHandler.h"
#include <esp_timer.h>

#define DEBOUNCE_DELAY 150

bool button_pressed[34];
long long button_pressed_time;
long time_ms;

void gpio_isr_handler(void *arg) {
    long long currentTime = esp_timer_get_time();

    if ((button_pressed_time + (DEBOUNCE_DELAY * 1000)) < currentTime) {
        button_pressed[(int)arg] = true;
        button_pressed_time = currentTime;
    }
}

bool is_button_pressed(gpio_num_t gpioNum) {
    if (button_pressed[gpioNum]) {
        button_pressed[gpioNum] = 0;
        return true;
    }
    else {
        return false;
    }
}


void add_button(gpio_num_t gpioNum) {
    //setup button interrupt
    //zero-initialize the config structure.
    gpio_config_t io_conf;
    //SwitchA Interrupt
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = 1UL<< gpioNum;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    //change gpio interrupt type for one pin
    gpio_set_intr_type(gpioNum, GPIO_INTR_POSEDGE);


    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin

    gpio_isr_handler_add(gpioNum, gpio_isr_handler, (void*) gpioNum);
}