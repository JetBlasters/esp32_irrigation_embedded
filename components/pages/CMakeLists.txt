set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_SRCS "Page.cpp" "main-page.cpp" "settings-page.cpp" "DateTimePage.cpp" "OptionsPage.cpp"
         "EditJobsPage.cpp" "EditJobPage.cpp" "FilterSchedulesPage.cpp" "EditRunsPage.cpp"
        "EditRunPage.cpp" "EditProgramsPage.cpp" "EditProgramPage.cpp.cpp")
idf_component_register(SRC_DIRS "."
        REQUIRES navigation-manager
        REQUIRES esp32-i2c-lcd1602
        REQUIRES esp32-smbus
        REQUIRES settings
        REQUIRES esp_timer
        REQUIRES fields
        REQUIRES options
        INCLUDE_DIRS "."
        "include")