project(CactRie)
file(GLOB_RECURSE SOURCES src/*.cpp src/*.cc)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

add_library(cactrie ${SOURCES} ${HEADERS})
target_include_directories(cactrie PUBLIC include)
target_link_libraries(cactrie cact-parser)

add_executable(cact-rie apps/cact-rie.cc)
target_link_libraries(cact-rie cactrie)

set(CACTRIE_TEST_SUITES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
add_executable(cact-rie-tests tests/cact-rie-tests.cc)
add_definitions(-DTEST_SUITES_DIR="${CACTRIE_TEST_SUITES_DIR}")
target_link_libraries(cact-rie-tests cactrie)