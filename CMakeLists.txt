cmake_minimum_required(VERSION 3.21)
project(cTion C)

set(CMAKE_C_STANDARD 99)
add_executable(cTion main.c)

#add gtk library
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(cTion ${GTK3_LIBRARIES})

#add curl library
find_package (CURL)
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(cTion ${CURL_LIBRARIES})
else()
    MESSAGE(FATAL_ERROR "LibCurl is not found in your system.")
endif (CURL_FOUND)

#add mysql library
target_link_libraries(cTion libmysqlclient.so)











