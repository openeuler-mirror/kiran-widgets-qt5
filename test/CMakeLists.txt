cmake_minimum_required(VERSION 3.5)

enable_testing()
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

add_executable(kiran-application-test kiran-application-test.cpp)
add_test(NAME kiran-application-test COMMAND kiran-application-test)
target_link_libraries(kiran-application-test Qt5::Test kiranwidgets-qt5)

add_executable(kiran-image-selector-test kiran-image-selector-test.cpp)
add_test(NAME kiran-image-selector-test COMMAND kiran-image-selector-test)
target_link_libraries(kiran-image-selector-test Qt5::Test kiranwidgets-qt5)

add_executable(kiran-message-box-test kiran-message-box-test.cpp)
add_test(NAME kiran-message-box-test COMMAND kiran-message-box-test)
target_link_libraries(kiran-message-box-test Qt5::Test kiranwidgets-qt5)

add_executable(kiran-sidebar-widget-test kiran-sidebar-widget-test.cpp)
add_test(NAME kiran-sidebar-widget-test COMMAND kiran-sidebar-widget-test)
target_link_libraries(kiran-sidebar-widget-test Qt5::Test kiranwidgets-qt5)

add_subdirectory(kiranwidgets-test)