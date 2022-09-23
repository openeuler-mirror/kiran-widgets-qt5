cmake_minimum_required(VERSION 3.5)

enable_testing()
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Test REQUIRED)

macro(ADD_TEST_ENTRY ENTRY_NAME)
    add_executable(${ENTRY_NAME} ${ENTRY_NAME}.cpp)
    add_test(NAME ${ENTRY_NAME} COMMAND ${ENTRY_NAME})
    target_link_libraries(${ENTRY_NAME} Qt5::Test kiranwidgets-qt5)
endmacro()

ADD_TEST_ENTRY(kiran-application-test)
ADD_TEST_ENTRY(kiran-image-selector-test)
ADD_TEST_ENTRY(kiran-message-box-test)
ADD_TEST_ENTRY(kiran-sidebar-widget-test)
ADD_TEST_ENTRY(kiran-hover-tips-test)
ADD_TEST_ENTRY(kiran-tips-test)