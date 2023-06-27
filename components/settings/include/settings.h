//
// Created by rgray on 8/02/2023.
//

#ifndef IRRIGATION_CONTROLLER_SETTINGS_H
#define IRRIGATION_CONTROLLER_SETTINGS_H

#include "esp_sntp.h"
#include "Job.h"
#include <vector>
#include <memory>
#include <esp_spiffs.h>
#include <string>

#define STORAGE_NAMESPACE "irrigation"
#define SCHEDULES_KEY "schedule"

using namespace std;

class settings {
public:
    static void set_time(time_t time);
    static time_t get_time();
    static esp_err_t save_job(const std::shared_ptr<Job>& job);
    static esp_err_t retrieve_job(const std::string& path, std::shared_ptr<Job> *jobOut);
    static esp_err_t retrieve_jobs(std::vector<std::shared_ptr<Job>>* jobsOut);
    static esp_err_t delete_job(std::shared_ptr<Job> job);
    static esp_err_t spiffs_init();
    static esp_err_t spiffs_close();

private:
    //static std::vector<std::shared_ptr<schedule>> _schedule_cache;

    constexpr static esp_vfs_spiffs_conf_t conf = {
            .base_path = "/spiffs",
            .partition_label = nullptr,
            .max_files = 5,
            .format_if_mount_failed = true
    };
};


#endif //IRRIGATION_CONTROLLER_SETTINGS_H
