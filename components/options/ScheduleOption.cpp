//
// Created by rgray on 19/06/2023.
//

#include "ScheduleOption.h"
#include "Job.h"

std::shared_ptr<Job> ScheduleOption::getJob() {
    return job;
}

std::string ScheduleOption::toString() {
    return job->toString();
}

bool ScheduleOption::handleSelect() {
    function(job);
    return false;
}
