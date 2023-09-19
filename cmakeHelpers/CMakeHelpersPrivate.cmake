function(traceGeneratorExpressionPrivate)
    if (${ARGC} GREATER  0)
    set (message "=============================[TRACE IN] ==> ${ARGV1}/CMakeLists.txt\n=============================[MESSAGE] : ${ARGV0}\n")
    endif()
    file(GENERATE OUTPUT traceFile.txt CONTENT ${message})
endfunction()

function(tracePrivate)
    if (${ARGC} GREATER  0)
        set (message "\n=============================[TRACE IN] ==> ${ARGV1}/CMakeLists.txt\n=============================[MESSAGE] : ${ARGV0}")
    endif()

    message("${message}")
endfunction()

function(addCommonChecksPrivate Target TargetType)
    if (UNIX)
        list (APPEND COMPILE_OPTIONS -Wall)

        if (ENABLE_SANITIZERS)
            list(APPEND COMPILE_OPTIONS -fsanitize=undefined -fsanitize=address -O2)

            addCppCheck()
            addClangTidy(${Target})
            addIncludeWhatYouUse(${Target})
        endif()

        target_compile_options(${This} ${TargetType}  ${COMPILE_OPTIONS})
        target_link_options(${This} ${TargetType}  ${COMPILE_OPTIONS})
    endif (UNIX)
endfunction()