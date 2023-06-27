set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_SRCS "Settings.cpp")
idf_component_register(SRC_DIRS "."
        REQUIRES pages
        REQUIRES nvs_flash
        REQUIRES spiffs
        REQUIRES jobs
        INCLUDE_DIRS "."
        "include")