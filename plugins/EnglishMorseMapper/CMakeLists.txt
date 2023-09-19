cmake_minimum_required(VERSION 3.16)

set(This EnglishMorseMapper)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 COMPONENTS Quick REQUIRED)

qt_add_library(${This} STATIC)

target_link_libraries(${This} PRIVATE Qt6::Quick BidirectionalMapper TextTokenizer)
set_target_properties(${This} PROPERTIES AUTOMOC ON)

qt_add_qml_module(${This} 
    URI ${This}
    VERSION 1.0
    SOURCES EnglishMorseMapper.hpp EnglishMorseMapper.cpp
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${This}
    RESOURCE_PREFIX /obrodskyi/imports
)

target_compile_definitions(${This} 
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

#outputBinaries(${This})
