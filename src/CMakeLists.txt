set(This EnglishMorseConverter)

find_package(Qt6 6.5 COMPONENTS Quick Gui REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(${This} main.cpp)
qt_add_qml_module(${This}
    URI ${This}
    VERSION 1.0
    QML_FILES gui/Main.qml gui/MainLoadable.qml
    OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${This}
    RESOURCE_PREFIX /obrodskyi/imports
)

target_include_directories(${This} PRIVATE
                           ${CMAKE_SOURCE_DIR}/plugins/QMLLiveReloader
                           ${CMAKE_SOURCE_DIR}/plugins/EnglishMorseMapper)
target_link_libraries(${This} PRIVATE Qt6::Quick QMLLiveReloaderplugin EnglishMorseMapperplugin)
target_compile_definitions(${This} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

addCommonChecks(${This})
outputBinaries(${This})