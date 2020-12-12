cmake_minimum_required(VERSION 3.5)

project(kiran-style-test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")

find_package(Qt5 COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        ${FORMS})

target_include_directories(${PROJECT_NAME} PRIVATE
        ../../src/widgets/kiran-application/
        ../../src/kiran-style/
        ../../src/widgets/kiran-switch-button
        ../../src/widgets/kiran-search-box
        ../../src/widgets/kiran-titlebar-window)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets kiranwidgets-qt5)