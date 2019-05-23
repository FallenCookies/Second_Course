cmake_minimum_required(VERSION 3.10)
project(Second_FinalProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(Second_FinalProject main.cpp date.h date.cpp database.h node.h token.cpp token.h condition_parser.h condition_parser.cpp  test_runner.h condition_parser_test.cpp test_runner.cpp node.cpp database.cpp Tests.h)