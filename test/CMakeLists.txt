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
        ${CMAKE_SOURCE_DIR}/src/Repl.cpp
        ${CMAKE_SOURCE_DIR}/src/AST.cpp
        ${CMAKE_SOURCE_DIR}/src/Parser.cpp
        )

set(TEST_CASES
        parser/LetStatementTest.cpp
        lexer_test.cpp
        )

add_executable(unittest ${TEST_CASES} ${TEST_SOURCES})

target_link_libraries(unittest Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(unittest)