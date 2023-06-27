//
// Created by rgray on 6/02/2023.
//
#ifndef IRRIGATION_CONTROLLER_NAVIGATIONMANAGER_H
#define IRRIGATION_CONTROLLER_NAVIGATIONMANAGER_H

#include "Page.h"
#include <memory>

std::shared_ptr<Page> pop_page();
void push_page(std::shared_ptr<Page> page);
std::shared_ptr<Page> current_page();
#endif //IRRIGATION_CONTROLLER_NAVIGATIONMANAGER_H
