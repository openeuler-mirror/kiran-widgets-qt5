cmake_minimum_required(VERSION 3.5)

option(build-kiran-test "build kiran style test" ON)

if( build-kiran-test )
add_subdirectory(kiran-style)
endif()

