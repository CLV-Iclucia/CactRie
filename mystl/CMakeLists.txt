file(GLOB MYSTL_HEADERS include)

add_library(mystl INTERFACE ${MYSTL_HEADERS})
target_include_directories(mystl INTERFACE include)

file(GLOB TESTS tests/*.cc)
foreach (TEST ${TESTS})
    get_filename_component(TEST_NAME ${TEST} NAME_WE)
    add_executable(${TEST_NAME} ${TEST})
    target_link_libraries(${TEST_NAME} mystl gtest gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach ()