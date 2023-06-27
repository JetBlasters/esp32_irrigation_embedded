//
// Created by rgray on 6/02/2023.
//

#include "Page.h"
#include "NavigationManager.h"
#include <memory>

std::vector<std::shared_ptr<Page>> pageStack;

void push_page(std::shared_ptr<Page> page) {
    page->display_page();
    pageStack.emplace_back(std::move(page));
}

std::shared_ptr<Page> pop_page() {
    if (pageStack.size() <= 1) {
        return nullptr;
    }
    
    std::shared_ptr<Page> lastElement = std::move(pageStack.back());
    pageStack.pop_back();
    current_page()->display_page();
    return lastElement;
}

std::shared_ptr<Page> current_page() {
    return pageStack.back();
}
