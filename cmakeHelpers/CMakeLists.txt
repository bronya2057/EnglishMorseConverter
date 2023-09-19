include(CMakeHelpersPrivate)

#================MAIN=========================
function(addCommonChecks Target)
    addCommonChecksPrivate(${Target} PRIVATE)
endfunction()

function(addCommonChecksInterface Target)
    addCommonChecksPrivate(${Target} INTERFACE)
endfunction()

#=================LOG=========================
function(trace)
    tracePrivate(${ARGV0} ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

function(traceGeneratorExpression)
    traceGeneratorExpressionPrivate(${ARGV0} ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

function(traceVars)
    message("=============[CMAKE_VARIABLES]============")
    message("[INSTALL_DIR] = ${CMAKE_INSTALL_PREFIX}")
    message("[ROOT_CMAKE] = ${CMAKE_SOURCE_DIR}")
    message("[CMAKE_BINARY_DIR] = ${CMAKE_BINARY_DIR}")
    message("[CMAKE_MODULE_PATH] = ${CMAKE_MODULE_PATH}")
    message("[CMAKE_PREFIX_PATH] = ${CMAKE_PREFIX_PATH}")
    message("[ENABLE_SANITIZERS] = ${ENABLE_SANITIZERS}")
    message("[GEN_GRAPHVIZ] = ${GEN_GRAPHVIZ}")
    message("[COVERAGE_ON] = ${COVERAGE_ON}")
    message("=============[CMAKE_VARIABLES_END]========")
endfunction()

#================FETCH========================
set(FETCHCONTENT_QUIET FALSE)

function(installGoogleTest)
    message("Fetching google test ...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        #GIT_TAG        release-1.11.0
        GIT_TAG main # latest commit
      )
    if (WIN32)
        # Prevent overriding the parent project's compiler/linker settings
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)
endfunction()

function(installGoogleBenchmark)
    message("Fetching google benchmark ...")
    include(FetchContent)
    FetchContent_Declare(benchmark
                         GIT_REPOSITORY https://github.com/google/benchmark.git
                         GIT_TAG c05843a9f622db08ad59804c190f98879b76beba # release-1.10.0
                         GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(benchmark)
endfunction()

macro(includeClangFormat target)
    find_program(CLANG-FORMAT_PATH clang-format REQUIRED)

    if (CLANG-FORMAT_PATH)
        set(directory ${CMAKE_CURRENT_SOURCE_DIR})
        trace("clang-format found")
        set(EXPRESSION h hpp hh c cc cxx cpp)
        list(TRANSFORM EXPRESSION PREPEND "${directory}/*.")
        file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
            LIST_DIRECTORIES false ${EXPRESSION}
        )
        add_custom_command(TARGET ${target} PRE_BUILD COMMAND
            ${CLANG-FORMAT_PATH} -i --style=file ${SOURCE_FILES}
        )
    endif()

endmacro()

#=====================DEPLOY================
function (outputBinaries Target)
    set (DESTINATION ${Target})

    if (${ARGC} GREATER 1)
        set (DESTINATION ${ARGN})
        message("Deploy ${DESTINATION} ---> ${Target}")
    endif()

    set_target_properties(${DESTINATION}
            PROPERTIES        
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${Target}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/${Target}"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${Target}"
    )
endfunction()


#==========================COVERAGE===============================
function (generateCoverageTarget)
    trace("coverage on")
    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)
    set(CMAKE_CXX_FLAGS "-O0 -coverage")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -coverage")

    add_custom_target(coverage_custom
    # gather data
    COMMAND ${LCOV} -c -d ${CMAKE_SOURCE_DIR} -o lcov_base.info
    COMMAND ${LCOV} --remove lcov_base.info '/usr/include/*' '${CMAKE_BINARY_DIR}/_deps/*' -o filtered_coverage.info
    #COMMAND ${LCOV} --directory . --capture --output-file coverage.info
    # generate report
    #--demangle-cpp -o coverage coverage.info
    COMMAND ${GENHTML} filtered_coverage.info --output-directory out
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()

# Usage: 
# 1. Build and run app. 
# 2. Build coverage custom target
# 3. Optionally use GCovViewer in vscode
function (addCoverage target)
    addCoveragePrivate(${target} PRIVATE)
endfunction()

function (addCoverageInterface target)
    addCoveragePrivate(${target} INTERFACE)
endfunction()

#====================STATIC ANALYZER==============================
# sudo apt install cppcheck
function(addCppCheck)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if (CMAKE_CXX_CPPCHECK)
        trace("CPPCheck found")
        list(
            APPEND CMAKE_CXX_CPPCHECK 
                "--enable=warning"
                "--inconclusive"
                "--force" 
                "--inline-suppr"
                "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
        )
    endif()
endfunction()

function(addClangTidy target)
  find_program(CLANG-TIDY_PATH clang-tidy REQUIRED)
  set_target_properties(${target}
    PROPERTIES CXX_CLANG_TIDY
    "${CLANG-TIDY_PATH}"
  )
endfunction()

# 1. git clone https://github.com/include-what-you-use/include-what-you-use.git
# 2. git checkout clang_Version.Minor e.g. clang_14.0
# 3. cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-7 ../include-what-you-use
# Troubleshoot sudo apt install libclang-14-dev

function(addIncludeWhatYouUse target)
    find_program(iwyu_path 
    NAMES include-what-you-use iwyu
    PATHS "/home/alex/Dev/include-what-you-use/build/bin/"
    NO_DEFAULT_PATH
    REQUIRED)

    if (iwyu_path)
        trace("iwyu found!")
    endif()

    set(CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endfunction()