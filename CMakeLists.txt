cmake_minimum_required(VERSION 3.10)
project(TinyLanguageCompiler) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)

add_executable(tiny_compiler src/main.cpp src/Lexer.cpp src/Parser.cpp)
