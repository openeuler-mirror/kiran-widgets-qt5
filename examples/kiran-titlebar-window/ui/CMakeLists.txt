cmake_minimum_required(VERSION 3.5)

project(kiran-titlebar-window-ui)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

find_package(Qt5 COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets kiranwidgets-qt5)