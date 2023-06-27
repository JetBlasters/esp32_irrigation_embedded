set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_SRCS "Option.cpp" "NamedOption.cpp" "FieldOption.cpp" "FunctionalOption.cpp" "ScheduleOption.cpp"
        "FunctionalFieldOption.cpp")
idf_component_register(SRC_DIRS "."
        REQUIRES settings
        INCLUDE_DIRS "."
        "include")