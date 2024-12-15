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
        ${SOURCE_DIR}/Order
        ${SOURCE_DIR}/Order
        ${SOURCE_DIR}/OrderStack
        ${SOURCE_DIR}/OrderManager/
        ${SOURCE_DIR}/Robot
        ${SOURCE_DIR}/Client
        ${SOURCE_DIR}/WarehouseManager
        ${SOURCE_DIR}/EventManager
)

set(TEST_DIRECTORIES
        ${SOURCE_DIR} 
        ${TEST_DIR} 
        ${INCLUDE_HEADERS}
)

add_executable(main_app
        main.cpp
        ${ORDER_SOURCES}
)
target_include_directories(main_app PRIVATE
        ${SOURCE_DIR}
        ${INCLUDE_HEADERS}
)

add_library(order_lib STATIC ${ORDER_SOURCES})
target_include_directories(order_lib PUBLIC
        ${SOURCE_DIR}
        ${INCLUDE_HEADERS}
)

find_package(GTest REQUIRED)

add_executable(test_order ${TEST_DIR}/test_order.cpp)
target_include_directories(test_order PRIVATE ${TEST_DIRECTORIES})
target_link_libraries(test_order PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

add_executable(test_order_stack ${TEST_DIR}/test_order_stack.cpp)
target_include_directories(test_order_stack PRIVATE ${TEST_DIRECTORIES})
target_link_libraries(test_order_stack PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

add_executable(test_order_manager ${TEST_DIR}/test_order_manager.cpp)
target_include_directories(test_order_manager PRIVATE ${TEST_DIRECTORIES})
target_link_libraries(test_order_manager PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

add_executable(test_robot ${TEST_DIR}/test_robot.cpp)
target_include_directories(test_robot PRIVATE ${TEST_DIRECTORIES})
target_link_libraries(test_robot PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

add_executable(test_client ${TEST_DIR}/test_client.cpp)
target_include_directories(test_client PRIVATE ${TEST_DIRECTORIES})
target_link_libraries(test_client PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

add_executable(test_warehouse_manager ${TEST_DIR}/test_warehouse_manager.cpp)
target_include_directories(test_warehouse_manager PRIVATE ${TEST_DIRECTORIES})
target_link_libraries(test_warehouse_manager PRIVATE order_lib GTest::gtest GTest::gtest_main pthread)

enable_testing()
add_test(NAME OrderTest COMMAND test_order)
add_test(NAME OrderStackTest COMMAND test_order_stack)
add_test(NAME OrderManagerTest COMMAND test_order_manager)
add_test(NAME RobotTest COMMAND test_robot)
add_test(NAME ClientTest COMMAND test_client)
add_test(NAME WarehouseManager COMMAND test_warehouse_manager)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/log)
