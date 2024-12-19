cmake_minimum_required(VERSION 3.16)
project(architecture_software_systems)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/code)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(LOG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/log)

file(MAKE_DIRECTORY ${LOG_DIR})

set(ORDER_SOURCES
        ${SOURCE_DIR}/Order/order.cpp
        ${SOURCE_DIR}/Order/counter.cpp
        ${SOURCE_DIR}/OrderStack/orderstack.cpp
        ${SOURCE_DIR}/OrderManager/ordermanager.cpp
        ${SOURCE_DIR}/Robot/robot.cpp
        ${SOURCE_DIR}/Client/client.cpp
        ${SOURCE_DIR}/WarehouseManager/warehousemanager.cpp
        ${SOURCE_DIR}/EventManager/eventmanager.cpp
)

set(ORDER_HEADERS
        ${SOURCE_DIR}/Order/order.h
        ${SOURCE_DIR}/Order/execution_status.h
        ${SOURCE_DIR}/Order/counter.h
        ${SOURCE_DIR}/OrderStack/orderstack.h
        ${SOURCE_DIR}/OrderManager/ordermanager.h
        ${SOURCE_DIR}/Robot/robot.h
        ${SOURCE_DIR}/Client/client.h
        ${SOURCE_DIR}/WarehouseManager/warehousemanager.h
        ${SOURCE_DIR}/EventManager/eventmanager.h
)

set(INCLUDE_HEADERS
        ${SOURCE_DIR}/Order
        ${SOURCE_DIR}/OrderStack
        ${SOURCE_DIR}/OrderManager
        ${SOURCE_DIR}/Robot
        ${SOURCE_DIR}/Client
        ${SOURCE_DIR}/WarehouseManager
        ${SOURCE_DIR}/EventManager
        ${SOURCE_DIR}/Application
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(APPLICATION_SOURCES
        main.cpp
        ${SOURCE_DIR}/Application/mainwindow.cpp
        ${SOURCE_DIR}/Application/mainwindow.ui
)

set(APPLICATION_HEADERS
        ${SOURCE_DIR}/Application/mainwindow.h
)

set(APPLICATION_FILES
        ${APPLICATION_HEADERS}
        ${APPLICATION_SOURCES}
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(application
            MANUAL_FINALIZATION
            ${APPLICATION_FILES}
    )
else ()
    add_executable(application
            ${APPLICATION_FILES}
    )
endif ()

if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.application)
endif ()

set_target_properties(application PROPERTIES
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
        MACOSX_BUNDLE "TRUE"
        WIN32_EXECUTABLE "TRUE"
)

if (BUNDLE_ID_OPTION)
    set_target_properties(application PROPERTIES ${BUNDLE_ID_OPTION})
endif()

include(GNUInstallDirs)
install(TARGETS application
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(application PRIVATE Qt6::Widgets)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(application)
endif ()

target_link_libraries(application PRIVATE order_lib)

add_library(order_lib STATIC ${ORDER_SOURCES})
target_include_directories(order_lib PUBLIC
        ${SOURCE_DIR}
        ${INCLUDE_HEADERS}
)

find_package(GTest REQUIRED)

set(TEST_SOURCES
        ${TEST_DIR}/test_order.cpp
        ${TEST_DIR}/test_order_stack.cpp
        ${TEST_DIR}/test_order_manager.cpp
        ${TEST_DIR}/test_robot.cpp
        ${TEST_DIR}/test_client.cpp
        ${TEST_DIR}/test_warehouse_manager.cpp
)

foreach (test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_include_directories(${test_name} PRIVATE ${TEST_DIR} ${SOURCE_DIR} ${INCLUDE_HEADERS})
    target_link_libraries(${test_name} PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach ()

enable_testing()
