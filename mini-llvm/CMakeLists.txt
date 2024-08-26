project(MiniLLVM)
file(GLOB_RECURSE SOURCES src/*.cpp src/*.cc)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)

add_library(mini-llvm ${SOURCES} ${HEADERS})
target_include_directories(mini-llvm PUBLIC include)