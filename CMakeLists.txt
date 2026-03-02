cmake_minimum_required(VERSION 3.25)
project(code C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

# NF - Define a variable for the testing directory
set(TESTING_DIR "${CMAKE_SOURCE_DIR}/testing")
set(XML_TO_MD_EXECUTABLE "${CMAKE_BINARY_DIR}/xml_to_md.exe")

# Collect all source files (excluding test files and main.c)
file(GLOB LIB_SOURCES "*.c")
message("All source files: ${LIB_SOURCES}")
list(FILTER LIB_SOURCES EXCLUDE REGEX "test_.*\\.c$")
list(FILTER LIB_SOURCES EXCLUDE REGEX "main\\.c$")

# Main executable
add_executable(RSA main.c ${LIB_SOURCES})

# Auto-discover test files and create test executables
enable_testing()

#add a dummy test to clean up old reports before running new tests
add_test(NAME CLEANING_TEST_REPORT COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/test_reports/all_tests.md)
set_tests_properties(CLEANING_TEST_REPORT PROPERTIES FIXTURE_SETUP clean_fixture LABELS "CLEANUP")

file(GLOB TEST_FILES "${TESTING_DIR}/test_*.c")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

   add_executable(${TEST_NAME} ${TEST_FILE} ${LIB_SOURCES})

    add_custom_command(
            TARGET ${TEST_NAME}
            POST_BUILD
            COMMAND $<TARGET_FILE:${TEST_NAME}> run --output=${CMAKE_SOURCE_DIR}/test_reports/${TEST_NAME}.xml || ${CMAKE_COMMAND} -E true
            # echo "Running ${TEST_NAME} and generating XML report..."
            COMMAND ${CMAKE_COMMAND} -E echo "Running ${TEST_NAME} and generating XML report..."
            COMMAND ${XML_TO_MD_EXECUTABLE} ${CMAKE_SOURCE_DIR}/test_reports/${TEST_NAME}.xml
    )



    file(READ ${TEST_FILE} TEST_SOURCE)
    string(REGEX MATCHALL "UTEST\\([^,]+,[^)]+\\)" TEST_MATCHES "${TEST_SOURCE}")

    foreach(match ${TEST_MATCHES})
        string(REGEX REPLACE "UTEST\\([ ]*([^, ]+)[ ]*,[ ]*([^) ]+)[ ]*\\)" "\\1.\\2" TEST_CASE "${match}")
        add_test(
                NAME ${TEST_NAME}.${TEST_CASE}
                COMMAND ${CMAKE_COMMAND}
                -DTEST_EXECUTABLE=$<TARGET_FILE:${TEST_NAME}>
                -DFILTER=${TEST_CASE}
                -DXML_REPORT=${CMAKE_SOURCE_DIR}/test_reports/${TEST_NAME}.${TEST_CASE}.xml
                -DXML_TO_MD_EXECUTABLE=${XML_TO_MD_EXECUTABLE}
                -P "${TESTING_DIR}/run_tests.cmake"
        )
        set_tests_properties(${TEST_NAME}.${TEST_CASE} PROPERTIES TIMEOUT 30 LABELS "unit" FIXTURE_REQUIRED clean_fixture)
    endforeach()


endforeach()

# Check if 'xml_to_md.exe' exists in the build directory

if(NOT EXISTS ${XML_TO_MD_EXECUTABLE})
    message(STATUS "Executable 'xml_to_md.exe' not found. Building it during configuration...")

    # Build 'xml_to_md.exe' using execute_process
    execute_process(
            COMMAND ${CMAKE_C_COMPILER} ${TESTING_DIR}/xml_to_md.c -o ${XML_TO_MD_EXECUTABLE}
            RESULT_VARIABLE BUILD_RESULT
            ERROR_VARIABLE BUILD_ERROR
    )

    # Check if the build was successful
    if(NOT BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to build 'xml_to_md.exe': ${BUILD_ERROR}")
    endif()
endif()

