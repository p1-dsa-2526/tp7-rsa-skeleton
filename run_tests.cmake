# Run the test
execute_process(
        COMMAND ${TEST_EXECUTABLE} --filter=${FILTER} --output=${XML_REPORT}
        RESULT_VARIABLE TEST_RESULT
)

if(NOT EXISTS ${XML_TO_MD_EXECUTABLE})
    message(FATAL_ERROR "Executable '${XML_TO_MD_EXECUTABLE}' not found.")
endif()
# Run the conversion
execute_process(
        COMMAND ${XML_TO_MD_EXECUTABLE} ${XML_REPORT} --partial
)

# Propagate the test failure to CTest
if(NOT TEST_RESULT EQUAL 0)
    message(FATAL_ERROR "Test failed with return code ${TEST_RESULT}")
endif()