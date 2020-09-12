cmake_minimum_required(VERSION 3.10)

project(PHP LANGUAGES C)
#[[
    Note that extensions using C++ can enable it by doing:
    enable_language(CXX)
]]

find_program(BISON_EXECUTABLE bison)
if (BISON_EXECUTABLE)
    message("Found bison: ${BISON_EXECUTABLE}")
endif ()

find_program(RE2C_EXECUTABLE re2c)
if (RE2C_EXECUTABLE)
    message("Found re2c: ${RE2C_EXECUTABLE}")
endif ()

add_subdirectory(Zend)

