cmake_minimum_required(VERSION 3.10)
project(cTion C)

set(CMAKE_C_STANDARD 99)


add_executable(cTion test.c)

target_link_libraries(cTion libmysqlclient.so)
target_link_libraries(cTion libgraph.so)
#target_link_libraries(cTion conio.h)


