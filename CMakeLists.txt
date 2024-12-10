cmake_minimum_required(VERSION 3.22)
project(architecture_software_systems)

set(CMAKE_CXX_STANDARD 20)

# Основное приложение
add_executable(main_app
        main.cpp
        code/order.cpp
        code/order.h
        code/execution_status.h
        code/counter.h
        code/counter.cpp
        code/orderstack.cpp
        code/orderstack.h)
target_include_directories(main_app PRIVATE code)

# Тесты
find_package(GTest REQUIRED)
add_executable(test_order
        test/test_order.cpp
        code/order.cpp
        code/order.h
        code/execution_status.h
        code/counter.h
        code/counter.cpp
        code/orderstack.cpp
        code/orderstack.h
        test/test_order_stack.cpp)
target_include_directories(test_order PRIVATE code)
target_link_libraries(test_order GTest::gtest GTest::gtest_main pthread)

# Включить тестирование
enable_testing()
add_test(NAME OrderTests COMMAND test_order)
