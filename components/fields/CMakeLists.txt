set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_SRCS "Field.cpp" "TimeField.cpp" "ShortField.cpp" "DurationField.cpp"
        "DayField.cpp" "WeekField.cpp" "DateField.cpp" "StringField.cpp")
idf_component_register(SRC_DIRS "."
        REQUIRES settings
        INCLUDE_DIRS "."
        "include")