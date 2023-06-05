project(unittest VERSION 0.1.0)

# include(FetchContent)

# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v2.13.9 # or a later release
# )

# FetchContent_MakeAvailable(Catch2)
find_package(Catch2 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(TEST_SOURCES
        ${CMAKE_SOURCE_DIR}/src/Lexer.cpp
        ${CMAKE_SOURCE_DIR}/src/Token.cpp
        ../src/Repl.cpp ../include/Repl.h)

add_executable(unittest lexer_test.cpp ${TEST_SOURCES})

target_link_libraries(unittest Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(unittest)