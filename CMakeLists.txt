cmake_minimum_required(VERSION 3.10)
project(TinyLanguageCompiler) # Changed project name

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)

# We are using tiny_compiler now to avoid the naming conflict
add_executable(tiny_compiler src/main.cpp src/Lexer.cpp src/Parser.cpp)