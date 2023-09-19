cmake_minimum_required(VERSION 3.16)

project(EnglishMorseConverter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeHelpers")

add_subdirectory(cmakeHelpers)
traceVars()

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(lib)
add_subdirectory(plugins)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)

