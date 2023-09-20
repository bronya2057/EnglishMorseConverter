set(This TextTraits)
project(${This} C CXX)

find_package(Qt6 6.5 COMPONENTS Core REQUIRED)

add_library(${This} inc/TextTraits.hpp private/TextTraits.cpp)
add_library(${This}::${This} ALIAS ${This})
target_include_directories(${This} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(${This} PUBLIC Qt6::Core BidirectionalMapper)

addCommonChecks(${This})
addCoverage(${This})
outputBinaries(${This})