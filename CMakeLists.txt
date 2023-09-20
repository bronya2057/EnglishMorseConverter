cmake_minimum_required(VERSION 3.16)

project(EnglishMorseConverter LANGUAGES CXX)

#=====================CONFIG========================#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeHelpers")

option(TEST_CMAKE "Enable/Disable Google Test" OFF)
option(GEN_GRAPHVIZ "Generate Graphviz" OFF)
option(COVERAGE_ON "Enable coverage" OFF)
option(ENABLE_SANITIZERS "Enable additional sanitizers" OFF)

add_subdirectory(cmakeHelpers)
traceVars()

#=====================SRC========================#
add_subdirectory(lib)
add_subdirectory(plugins)
add_subdirectory(src)

#=====================TEST========================#
if(${TEST_CMAKE})
    enable_testing()
    add_subdirectory(test)
endif()

#================DEPENDENCY GRPAH===================#
if(${GEN_GRAPHVIZ})
    add_custom_target(graphviz ALL
        COMMAND ${CMAKE_COMMAND} "--graphviz=graphviz/foo.dot" .
        COMMAND dot -Tpng graphviz/foo.dot -o foo.png
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
endif()

#=====================COVERAGE========================#
if(${COVERAGE_ON})
    generateCoverageTarget()
endif()