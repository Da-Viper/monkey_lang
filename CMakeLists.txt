cmake_minimum_required(VERSION 3.0.0)
project(monkey_lang VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/include)
set(SOURCES
        src/Repl.cpp
        src/Lexer.cpp
        src/Token.cpp
        src/AST.cpp include/AST.h include/Parser.h src/Parser.cpp)


add_subdirectory(test)
add_executable(monkey_lang main.cpp ${SOURCES})
# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
