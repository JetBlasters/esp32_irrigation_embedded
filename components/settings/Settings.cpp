//
// Created by rgray on 8/02/2023.
//

#include "include/settings.h"
#include "esp_sntp.h"
#include "time.h"

#include "nvs_flash.h"
#include "nvs.h"

#include <cstdio>
#include <vector>
#include <esp_log.h>
#include <esp_spiffs.h>
#include <fstream>
#include <filesystem>
#include <sys/dirent.h>

#define TAG "SPIFFS"

using namespace std;

time_t settings::get_time() {
    time_t now;
    time(&now);
    return now;
}

void settings::set_time(time_t time) {
    struct timezone timezone{};
    struct timeval timeval{};
    timeval.tv_sec = time;
    timezone.tz_minuteswest = 0;
    settimeofday(&timeval, &timezone);
}
//
//std::vector<std::shared_ptr<schedule>> schedule_vector_deep_copy(std::vector<std::shared_ptr<schedule>> src) {
//    std::vector<std::shared_ptr<schedule>> copy;
//
//    for (std::shared_ptr<schedule> s : src) {
//        copy.push_back(std::make_shared<schedule>(s->getStation(), s->getDay(), s->getWeeksRun(),
//                                                  s->getTime(), s->getDuration()));
//    }
//
//    printf("Done\n");
//    return copy;
//}
//
//esp_err_t settings::get_schedules(std::vector<std::shared_ptr<schedule>>* schedulesOut) {
////    if (!_schedule_cache.empty()) {
////        printf("Getting cache\n");
////        *schedulesOut = schedule_vector_deep_copy(_schedule_cache);
////        return ESP_OK;
////    }
//    printf("Getting from NVS\n");
//
//    nvs_handle_t handle;
//    esp_err_t err;
//
//    // Open handle
//    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
//    if (err != ESP_OK) {
//        return err;
//    }
//
//    // read schedule blob
//    std::vector<schedule::ScheduleSave> scheduleSaves;
//    size_t required_size = 0;
//    // obtain required size first.
//    err = nvs_get_blob(handle, SCHEDULES_KEY, nullptr, &required_size);
//    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND) {
//        return err;
//    }
//
//    if (err == ESP_OK) {
//        // ensures the schedules vector has enough room.
//        printf("Newsize: %d\n", required_size/sizeof(schedule::ScheduleSave));
//        scheduleSaves.resize(required_size/sizeof(schedule::ScheduleSave));
//        err = nvs_get_blob(handle, SCHEDULES_KEY, scheduleSaves.data(), &required_size);
//        if (err != ESP_OK) {
//            return err;
//        }
//    }
//
//    nvs_close(handle);
//    std::vector<std::shared_ptr<schedule>> schedules;
//    for (schedule::ScheduleSave save : scheduleSaves) {
//        schedules.emplace_back(std::make_shared<schedule>(save));
//    }
//
//    printf("attempting copy\n");
////    _schedule_cache = schedule_vector_deep_copy(schedules);
//    printf("copy success\n");
//    *schedulesOut = schedules;
//    return ESP_OK;
//}
//
//esp_err_t settings::save_schedules(const std::vector<std::shared_ptr<schedule>>& schedules) {
//    std::vector<schedule::ScheduleSave> scheduleSaves;
//
//    for (std::shared_ptr<schedule> s : schedules) {
//        scheduleSaves.emplace_back(s->toSaveStruct());
//    }
//
//
//    nvs_handle_t handle;
//    esp_err_t err;
//
//    // Open handle
//    err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &handle);
//    if (err != ESP_OK) {
//        return err;
//    }
//
//    err = nvs_set_blob(handle, SCHEDULES_KEY, scheduleSaves.data(),
//                       scheduleSaves.size() * sizeof(schedule::ScheduleSave));
//    if (err != ESP_OK)  {
//        return err;
//    }
//
//    err = nvs_commit(handle);
//    if (err != ESP_OK) {
//        return err;
//    };
//
////    _schedule_cache = schedule_vector_deep_copy(schedules);
//
//    nvs_close(handle);
//    return ESP_OK;
//}

esp_err_t settings::spiffs_init() {
    ESP_LOGI(TAG, "Initializing SPIFFS");
    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return ret;
    }
//
//    ESP_LOGI(TAG, "Performing SPIFFS_check().");
//    ret = esp_spiffs_check(conf.partition_label);
//    if (ret != ESP_OK) {
//        ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
//        return ret;
//    } else {
//        ESP_LOGI(TAG, "SPIFFS_check() successful");
//    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s). Formatting...", esp_err_to_name(ret));
        esp_spiffs_format(conf.partition_label);
        return ret;
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }

    // Check consistency of reported partiton size info.
    if (used > total) {
        ESP_LOGW(TAG, "Number of used bytes cannot be larger than total. Performing SPIFFS_check().");
        ret = esp_spiffs_check(conf.partition_label);
        // Could be also used to mend broken files, to clean unreferenced pages, etc.
        // More info at https://github.com/pellepl/spiffs/wiki/FAQ#powerlosses-contd-when-should-i-run-spiffs_check
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "SPIFFS_check() failed (%s)", esp_err_to_name(ret));
            return ret;
        } else {
            ESP_LOGI(TAG, "SPIFFS_check() successful");
        }
    }

    return ESP_OK;
}

esp_err_t settings::spiffs_close() {
    // All done, unmount partition and disable SPIFFS
    esp_vfs_spiffs_unregister(conf.partition_label);
    ESP_LOGI(TAG, "SPIFFS unmounted");

    return ESP_OK;
}

esp_err_t settings::save_job(const std::shared_ptr<Job>& job) {
    std::ofstream jobFile;
    jobFile.open("/spiffs/" + job->getName() + ".job", std::ios_base::trunc);

    if (!jobFile) {
        ESP_LOGI(TAG, "Failed to open file for writing");
        return ESP_FAIL;
    }

    jobFile << job->getName() << "\n";
    if (!jobFile) {
        ESP_LOGI(TAG, "Failed to write data to file");
        return ESP_FAIL;
    }

    for (Job::StationProgram stationProgram : job->getStationPrograms()) {
        jobFile << stationProgram.station << "," << stationProgram.startDelay << "," << stationProgram.duration << "\n";
        if (!jobFile) {
            ESP_LOGI(TAG, "Failed to write data to file");
            return ESP_FAIL;
        }
    }

    jobFile << "\n";

    for (Job::Run run : job->getRuns()) {
        jobFile << run.time << "," << run.day << "," << run.weeksRun << "\n";
        if (!jobFile) {
            ESP_LOGI(TAG, "Failed to write data to file");
            return ESP_FAIL;
        }
    }

    jobFile.close();

    return ESP_OK;
}

vector<string> splitString(string str, string delimiter) {
    vector<string> tokens;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != string::npos) {
        tokens.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);
    return tokens;
}

unsigned short strToUS(string str) {
    char* end;
    unsigned short uShort = std::strtoul(str.c_str(), &end, 10);if (*end != '\0') {
        ESP_LOGI(TAG, "String to unsigned short conversion failed.");
        return 1;
    }

    return uShort;
}

esp_err_t settings::retrieve_job(const std::string& path, std::shared_ptr<Job> *jobOut) {
    string jobName;
    vector<Job::StationProgram> stationPrograms;
    vector<Job::Run> runs;


    ifstream jobFile(path);
    if (!jobFile) {
        ESP_LOGI(TAG, "Failed to open file for reading");
        return ESP_FAIL;
    }

    string line;
    if (getline(jobFile, line)) {
        jobName = line;
    } else {
        ESP_LOGI(TAG, "Malformed job file.");
        return ESP_FAIL;
    }

    while (getline(jobFile, line) && !line.empty()) {
        vector<string> tokens = splitString(line, ",");
        if (tokens.size() != 3) {
            ESP_LOGI(TAG, "Malformed job file.");
            return ESP_FAIL;
        }

        unsigned short station = strToUS(tokens.at(0));
        unsigned short startDelay = strToUS(tokens.at(1));
        unsigned short duration = strToUS(tokens.at(2));

        Job::StationProgram stationProgram = { station, startDelay, duration };

        stationPrograms.push_back(stationProgram);
    }

    while (getline(jobFile, line)) {
        vector<string> tokens = splitString(line, ",");
        if (tokens.size() != 3) {
            ESP_LOGI(TAG, "Malformed job file.");
            return ESP_FAIL;
        }

        unsigned short time = strToUS(tokens.at(0));
        auto day = static_cast<Job::DayOfWeek>(stoi(tokens.at(1)));
        auto weeksRun = static_cast<Job::WeeksRun>(stoi(tokens.at(2)));

        Job::Run run = { time, day, weeksRun };

        runs.push_back(run);
    }

    *jobOut = make_unique<Job>(jobName, stationPrograms, runs);

    return ESP_OK;
}

bool ends_with(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

esp_err_t settings::retrieve_jobs(std::vector<std::shared_ptr<Job>>* jobsOut) {
    std::vector<std::shared_ptr<Job>> jobs;

    DIR* dir;
    struct dirent *ent;

    if ((dir = opendir ("/spiffs")) != nullptr) {
        while ((ent = readdir (dir)) != nullptr) {
            // checks if it is a job file
            if (ends_with(ent->d_name, ".job")) {
                std::shared_ptr<Job> job;
                esp_err_t err = retrieve_job("/spiffs/" + string(ent->d_name), &job);

                if (err != ESP_OK) {
                    ESP_LOGI(TAG, "Failed parsing a job.");
                    return err;
                }

                jobs.push_back(std::move(job));
            }
        }
        closedir (dir);
    } else {
        ESP_LOGI(TAG, "Failed open spiffs directory.");
        return ESP_FAIL;
    }

    *jobsOut = std::move(jobs);

    return ESP_OK;
}

esp_err_t settings::delete_job(std::shared_ptr<Job> job) {
    if (remove(("/spiffs/" + job->getName() + ".job").c_str()) != 0) {
        ESP_LOGI(TAG, "Failed to delete job: %s.", job->getName().c_str());
        return ESP_FAIL;
    }

    return ESP_OK;
}
