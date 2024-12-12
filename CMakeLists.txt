cmake_minimum_required(VERSION 3.22)
project(architecture_software_systems)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/code)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

set(ORDER_SOURCES
        ${SOURCE_DIR}/Order/order.cpp
        ${SOURCE_DIR}/Order/counter.cpp
        ${SOURCE_DIR}/OrderStack/orderstack.cpp
        ${SOURCE_DIR}/OrderManager/ordermanager.cpp
        ${SOURCE_DIR}/Robot/robot.cpp
)

set(ORDER_HEADERS
        ${SOURCE_DIR}/Order/order.h
        ${SOURCE_DIR}/Order/execution_status.h
        ${SOURCE_DIR}/Order/counter.h
        ${SOURCE_DIR}/OrderStack/orderstack.h
        ${SOURCE_DIR}/OrderManager/ordermanager.h
        ${SOURCE_DIR}/Robot/robot.h
)

add_executable(main_app
        main.cpp
        ${ORDER_SOURCES}
)
target_include_directories(main_app PRIVATE ${SOURCE_DIR})

add_library(order_lib STATIC ${ORDER_SOURCES})
target_include_directories(order_lib PUBLIC ${SOURCE_DIR})

find_package(GTest REQUIRED)

add_executable(test_order ${TEST_DIR}/test_order.cpp)
target_include_directories(test_order PRIVATE ${SOURCE_DIR} ${TEST_DIR})
target_link_libraries(test_order PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

add_executable(test_order_stack ${TEST_DIR}/test_order_stack.cpp)
target_include_directories(test_order_stack PRIVATE ${SOURCE_DIR} ${TEST_DIR})
target_link_libraries(test_order_stack PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

add_executable(test_order_manager ${TEST_DIR}/test_order_manager.cpp)
target_include_directories(test_order_manager PRIVATE ${SOURCE_DIR} ${TEST_DIR})
target_link_libraries(test_order_manager PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

enable_testing()
add_test(NAME OrderTest COMMAND test_order)
add_test(NAME OrderStackTest COMMAND test_order_stack)
add_test(NAME OrderManagerTest COMMAND test_order_manager)
