cmake_minimum_required(VERSION 3.5)

project(kiran-application-example)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PkgConfig REQUIRED)
find_package(Qt5 COMPONENTS Widgets)
pkg_search_module(KIRAN_WIDGETS_QT5 REQUIRED kiranwidgets-qt5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${KIRAN_WIDGETS_QT5_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${KIRAN_WIDGETS_QT5_LIBRARIES})