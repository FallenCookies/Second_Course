cmake_minimum_required(VERSION 3.10)
project(Phone_number)

set(CMAKE_CXX_STANDARD 17)

add_executable(Phone_number main.cpp phone_number.h phone_number.cpp test_runner.h)