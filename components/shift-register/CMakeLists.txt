set(COMPONENT_ADD_INCLUDEDIRS include)
set(COMPONENT_SRCS "ShitRegister.cpp")
idf_component_register(SRC_DIRS "."
        REQUIRES pages
        INCLUDE_DIRS "."
        "include")