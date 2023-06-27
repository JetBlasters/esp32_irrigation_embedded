set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_SRCS "ButtonHandler.cpp")
idf_component_register(SRC_DIRS "."
        REQUIRES driver
        REQUIRES esp_timer
        INCLUDE_DIRS "."
        "include")