//
// Created by rgray on 19/06/2023.
//

#include "include/FilterSchedulesPage.h"
#include "FunctionalFieldOption.h"
#include "DayField.h"
#include "NavigationManager.h"
#include "EditJobsPage.h"
#include "FunctionalOption.h"
#include "ShortField.h"
#include <memory>

FilterSchedulesPage::FilterSchedulesPage(i2c_lcd1602_info_t *_lcd_info) : OptionsPage(_lcd_info) {
    add_option(std::make_shared<functionalOption>("Show all...", [_lcd_info] {
        push_page(std::make_shared<EditJobsPage>(_lcd_info));
    }));

//    std::shared_ptr<Job::DayOfWeek> day = std::make_shared<Job::DayOfWeek>(Job::Monday);
//    add_option(std::make_shared<FunctionalFieldOption>("Filter day",
//                                                       std::make_unique<DayField>(std::move(day)),
//                                                       [_lcd_info](const std::shared_ptr<void>& voidPtr) {
//        std::shared_ptr<schedule::DayOfWeek> day = std::static_pointer_cast<schedule::DayOfWeek>(voidPtr);
//        push_page(std::make_shared<EditJobsPage>(_lcd_info, *day));
//    }));
//
//    std::shared_ptr<unsigned short> station = std::make_shared<unsigned short>(1);
//    add_option(std::make_shared<FunctionalFieldOption>("Filter station",
//                                                       std::make_unique<ShortField>(std::move(station),
//                                                                                     1, 8),
//                                                       [_lcd_info](const std::shared_ptr<void>& voidPtr) {
//                                                           std::shared_ptr<unsigned short> station = std::static_pointer_cast<unsigned short>(voidPtr);
//                                                           push_page(std::make_shared<EditJobsPage>(_lcd_info, *station));
//                                                       }));
}
