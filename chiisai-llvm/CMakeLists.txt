project(ChiisaiLLVM)

option(LLVM_GENERATE_PARSER "Generate LLVM parser code using ANTLR-4" ON)

if (LLVM_GENERATE_PARSER)
    message(STATUS "Generating LLVM parser code using ANTLR-4")
    execute_process(
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/parser-codegen.sh "java" ${ANTLR_JAR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE result
            OUTPUT_VARIABLE output
            ERROR_VARIABLE error_output
    )
    message(STATUS "ANTLR-4 Code Generation Output:\n${output}")
    message(STATUS "ANTLR-4 Code Generation Error Output:\n${error_output}")
else ()
    message(STATUS "Globbing generated source files...")
endif ()

file(GLOB_RECURSE AUTO_GENERATED_HEADERS src/autogen/*.h src/autogen/*.hpp)
file(GLOB_RECURSE AUTO_GENERATED_SOURCES src/autogen/*.cpp src/autogen/*.cc)

add_library(chiisai-llvm-autogen ${AUTO_GENERATED_SOURCES} ${AUTO_GENERATED_HEADERS})
target_include_directories(chiisai-llvm-autogen PUBLIC include ${ANTLR_RUNTIME_INCLUDE_DIR}/antlr-runtime)
target_link_libraries(chiisai-llvm-autogen antlr-runtime)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.cc)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

add_library(chiisai-llvm ${SOURCES} ${HEADERS})
target_include_directories(chiisai-llvm PUBLIC include)
target_link_libraries(chiisai-llvm chiisai-llvm-autogen)