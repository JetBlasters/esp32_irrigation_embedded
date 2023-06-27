//
// Created by rgray on 19/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_SCHEDULEOPTION_H
#define IRRIGATION_CONTROLLER_SCHEDULEOPTION_H

#include "FunctionalOption.h"
#include "Job.h"
#include <memory>
#include <utility>

class ScheduleOption : public Option {
public:
    ScheduleOption(std::shared_ptr<Job> job, std::function<void(std::shared_ptr<Job>)> function) :
        job(std::move(job)), function(std::move(function)){};

    std::shared_ptr<Job> getJob();
    std::string toString() override;
    bool handleSelect() override;
private:
    std::shared_ptr<Job> job;
    std::function<void(std::shared_ptr<Job>)> function;
};


#endif //IRRIGATION_CONTROLLER_SCHEDULEOPTION_H
