cmake_minimum_required(VERSION 3.20)
project(cTion C)

set(CMAKE_C_STANDARD 99)
add_executable(cTion fileConfig.c)


target_link_libraries(cTion libmysqlclient.so)











