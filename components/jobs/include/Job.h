//
// Created by rgray on 22/06/2023.
//

#ifndef IRRIGATION_CONTROLLER_JOB_H
#define IRRIGATION_CONTROLLER_JOB_H


#include <string>
#include <utility>
#include <vector>
#include <memory>

#define SecondsInAMinute 60
#define SecondsInAnHour 3600
#define SecondsInADay 86400
#define SecondsInAWeek 604800

class Job {
public:
    typedef enum {
        WEEK1,
        WEEK2,
        BOTH
    } WeeksRun;

    typedef enum {
        Sunday = 0,
        Monday = 1,
        Tuesday = 2,
        Wednesday = 3,
        Thursday = 4,
        Friday = 5,
        Saturday = 6
    } DayOfWeek;

    typedef struct {
        // in seconds
        unsigned int time;
        DayOfWeek day;
        WeeksRun weeksRun;
    } Run;

    typedef struct {
        // in seconds
        unsigned short station;
        unsigned short startDelay;
        unsigned short duration;
    } StationProgram;

    Job(std::string name, std::vector<StationProgram> stationPrograms, std::vector<Run> runs)
        : name(std::move(name)), runs(std::move(runs)), stationPrograms(std::move(stationPrograms)) {}

    void addRun(Run run) {
        runs.push_back(run);
    }

    void updateRun(int index, Run run) {
        runs[index] = run;
    }

    void deleteRun(int index) {
        runs.erase(runs.begin() + index);
    }

    void addStationProgram(StationProgram program) {
        stationPrograms.push_back(program);
    }

    void updateStationProgram(int index, StationProgram program) {
        stationPrograms[index] = program;
    }

    void deleteStationProgram(int index) {
        stationPrograms.erase(stationPrograms.begin() + index);
    }

    std::vector<Run> getRuns() {
        return runs;
    }

    std::vector<StationProgram> getStationPrograms() {
        return stationPrograms;
    }

    std::string getName() {
        return name;
    }

    void setName(std::string newName) {
        name = std::move(newName);
    }

    std::string toString();
    unsigned short getDuration();
    static std::string durationToString(unsigned short duration);
    std::string runToString(Run run);
    static std::string stationProgramToString(StationProgram program);
    static std::string timeToString(unsigned int time);
    static std::string weeksRunString(WeeksRun weeks);
    static std::string weeksRunShortString(WeeksRun weeks);
    static std::string dayOfWeekString(DayOfWeek day);

    bool shouldJobRun(unsigned int time, DayOfWeek day, bool week);
    std::unique_ptr<Run> getCurrentRun(unsigned int time, DayOfWeek day, bool week);
    std::vector<int> getActiveStations(Run run, unsigned int time, DayOfWeek day);
    Job deepCopy();
private:
    std::string name;
    std::vector<Run> runs;
    std::vector<StationProgram> stationPrograms;
};


#endif //IRRIGATION_CONTROLLER_JOB_H
