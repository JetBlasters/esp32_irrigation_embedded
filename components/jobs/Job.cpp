//
// Created by rgray on 22/06/2023.
//

#include <sstream>
#include <memory>
#include "include/Job.h"

using namespace std;

string Job::toString() {
    ostringstream str;

    str << getName() << " " << durationToString(getDuration());

    return str.str();
}

unsigned short Job::getDuration() {
    unsigned short duration = 0;

    for (StationProgram stationProgram : stationPrograms) {
        unsigned short totalStationDuration = stationProgram.startDelay + stationProgram.duration;
        if (totalStationDuration > duration) {
            duration = totalStationDuration;
        }
    }

    return duration;
}

std::string Job::durationToString(unsigned short duration) {
    ostringstream str;
    unsigned short minutes = (duration % (SecondsInAnHour)) / (SecondsInAMinute);
    unsigned short hours = (duration) / (SecondsInAnHour);

    if (hours != 0) {
        str << hours << "h ";
    }

    str << minutes << "m";;

    return str.str();
}


std::string Job::timeToString(unsigned int time) {
    unsigned short hour = time/(SecondsInAnHour);
    unsigned short minute = (time % (SecondsInAnHour))/(SecondsInAMinute);

    std::ostringstream str;
    if (hour < 10) {
        str << "0";
    }
    str << hour << ":";
    if (minute < 10) {
        str << "0";
    }
    str << minute;

    return str.str();
}

std::string Job::runToString(Run run) {
    ostringstream str;
    str << dayOfWeekString(run.day) << " " << timeToString(run.time) << "-" << timeToString(run.time + getDuration())
        << weeksRunShortString(run.weeksRun);

    return str.str();
}

std::string Job::weeksRunString(WeeksRun weeks) {
    switch (weeks) {
        case WEEK1:
            return "Week 1";
        case WEEK2:
            return "Week 2";
        case BOTH:
            return "Both";
        default:
            return "N/A";
    }
}

std::string Job::weeksRunShortString(WeeksRun weeks) {
    switch (weeks) {
        case WEEK1:
            return "W1";
        case WEEK2:
            return "W2";
        case BOTH:
            return "";
        default:
            return "N/A";
    }
}

std::string Job::dayOfWeekString(DayOfWeek day) {
    switch (day) {
        case DayOfWeek::Monday:
            return "MON";
        case DayOfWeek::Tuesday:
            return "TUE";
        case DayOfWeek::Wednesday:
            return "WED";
        case DayOfWeek::Thursday:
            return "THU";
        case DayOfWeek::Friday:
            return "FRI";
        case DayOfWeek::Saturday:
            return "SAT";
        case DayOfWeek::Sunday:
            return "SUN";
        default:
            return "N/A";
    }
}

std::string Job::stationProgramToString(StationProgram program) {
    ostringstream str;

    str << "S" << program.station << " " << durationToString(program.startDelay) << " to "
        << durationToString(program.startDelay + program.duration);

    return str.str();
}

Job Job::deepCopy() {
    vector<Run> runsCopy(runs.begin(), runs.end());
    vector<StationProgram> stationProgramsCopy(stationPrograms.begin(), stationPrograms.end());

    return {getName(), stationProgramsCopy, runsCopy};
}

bool Job::shouldJobRun(unsigned int time, Job::DayOfWeek day, bool week) {
    unsigned int weekTime = time + (SecondsInADay) * (int)day;
    WeeksRun weeksRun = week ? WEEK1 : WEEK2;
    auto duration = getDuration();

    for (Run run : runs) {
        if (weeksRun != run.weeksRun && run.weeksRun != BOTH) {
            continue;
        }

        unsigned int runWeekTime = run.time + (SecondsInADay) * (int)run.day;

        if (weekTime >= runWeekTime && weekTime < runWeekTime + duration) {
            return true;
        }
    }

    return false;
}

unique_ptr<Job::Run> Job::getCurrentRun(unsigned int time, Job::DayOfWeek day, bool week) {
    unsigned int weekTime = time + (SecondsInADay) * (int)day;
    WeeksRun weeksRun = week ? WEEK1 : WEEK2;
    auto duration = getDuration();

    for (Run run : runs) {
        if (weeksRun != run.weeksRun && run.weeksRun != BOTH) {
            continue;
        }

        unsigned int runWeekTime = run.time + (SecondsInADay) * (int)run.day;

        if (weekTime >= runWeekTime && weekTime < runWeekTime + duration) {
            return make_unique<Job::Run>(run);
        }
    }

    return nullptr;
}

std::vector<int> Job::getActiveStations(Job::Run run, unsigned int time, Job::DayOfWeek day) {
    vector<int> activeStations;
    unsigned int currentTime = time + (SecondsInADay) * (int)day;
    unsigned int runStartTime = run.time + (SecondsInADay) * (int)day;
    unsigned short timeSinceStart = currentTime - runStartTime;

    for (StationProgram program : stationPrograms) {
        if (program.startDelay <= timeSinceStart && timeSinceStart < program.startDelay + program.duration) {
            activeStations.push_back(program.station);
        }
    }

    return activeStations;
}

