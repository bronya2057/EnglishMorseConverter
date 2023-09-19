cmake_minimum_required(VERSION 3.11.0)
installGoogleTest()
set(This SharedPtrTests)

include(CTest)

if(MSVC)
   foreach(_tgt gtest gtest_main gmock gmock_main)
   target_compile_definitions(${_tgt}
      PRIVATE
      "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
      )
   endforeach()
endif()

set(Sources
    main.cpp
    SharedPtrTest.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(
    ${This} PRIVATE
    GTest::gtest_main
    GTest::gmock_main
    SharedPtrLib
)
add_test(
    NAME ${This}
    COMMAND ${This}
)

include(GoogleTest)
gtest_discover_tests(${This})
#install (TARGETS gtest_main DESTINATION bin)

outputBinaries(${This} gtest_main)
outputBinaries(${This} gmock_main)
outputBinaries(${This})