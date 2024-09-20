cmake_minimum_required(VERSION 3.28)
project(CactRie)

set(CMAKE_CXX_STANDARD 20)

set(ANTLR4_MAJOR_VERSION 13)
set(ANTLR4_MINOR_VERSION 1)

set(ANTLR4_JAR_NAME antlr-4.${ANTLR4_MAJOR_VERSION}.${ANTLR4_MINOR_VERSION}-complete.jar)
set(ANTLR_JAR ${CMAKE_CURRENT_SOURCE_DIR}/deps/${ANTLR4_JAR_NAME})

add_subdirectory(deps/antlr-runtime)
add_subdirectory(cact-front-end)
add_subdirectory(chiisai-llvm)
add_subdirectory(cact-rie)