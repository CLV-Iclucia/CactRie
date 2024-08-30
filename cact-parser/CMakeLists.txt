project(cact-parser)

option(GENERATE_PARSER "Generate parser code using ANTLR-4" ON)

message(STATUS "ANTLR-4 jar path: ${ANTLR_JAR}")
if (GENERATE_PARSER)
    message(STATUS "Generating parser code using ANTLR-4")
    execute_process(
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/parser-codegen.sh "java" ${ANTLR_JAR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error_output
    )
    message(STATUS "ANTLR-4 Code Generation Output:\n${output}")
    message(STATUS "ANTLR-4 Code Generation Error Output:\n${error_output}")
else()
    message(STATUS "Globbing generated source files...")
endif()
file(GLOB_RECURSE CACT_PARSER_AUTOGEN_SOURCES autogen/src/*.cpp autogen/src/*.cc autogen/include/*.h autogen/include/*.hpp)
file(GLOB_RECURSE CACT_PARSER_SOURCES src/*.cpp src/*.cc include/*.h include/*.hpp)

add_library(cact-parser ${CACT_PARSER_SOURCES} ${CACT_PARSER_AUTOGEN_SOURCES})
target_link_libraries(cact-parser PUBLIC antlr-runtime)
target_include_directories(cact-parser
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/autogen/include
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/autogen/include/cact-parser
        PUBLIC ${ANTLR_RUNTIME_INCLUDE_DIR}/antlr-runtime
)