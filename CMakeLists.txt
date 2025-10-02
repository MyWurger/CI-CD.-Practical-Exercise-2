cmake_minimum_required(VERSION 3.16)
project(calculator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(calc_lib src/calc.cpp)
target_include_directories(calc_lib PUBLIC src)

add_executable(calc_app src/main.cpp)
target_link_libraries(calc_app PRIVATE calc_lib)

enable_testing()

# Модульные Тесты
add_executable(test_basic_operations tests/unit/test_basic_operations.cpp)
target_link_libraries(test_basic_operations PRIVATE calc_lib)
target_include_directories(test_basic_operations PRIVATE src tests/utils)

add_executable(test_advanced_operations tests/unit/test_advanced_operations.cpp)
target_link_libraries(test_advanced_operations PRIVATE calc_lib)
target_include_directories(test_advanced_operations PRIVATE src tests/utils)

# Интеграционные Тесты
add_executable(test_eval_line tests/integration/test_eval_line.cpp)
target_link_libraries(test_eval_line PRIVATE calc_lib)
target_include_directories(test_eval_line PRIVATE src tests/utils)

# Граничные Случаи Тесты
add_executable(test_boundary_conditions tests/edge_cases/test_boundary_conditions.cpp)
target_link_libraries(test_boundary_conditions PRIVATE calc_lib)
target_include_directories(test_boundary_conditions PRIVATE src tests/utils)

# Регистрируем тесты с CTest
add_test(NAME unit_basic_operations COMMAND test_basic_operations)
add_test(NAME unit_advanced_operations COMMAND test_advanced_operations)
add_test(NAME integration_eval_line COMMAND test_eval_line)
add_test(NAME edge_boundary_conditions COMMAND test_boundary_conditions)