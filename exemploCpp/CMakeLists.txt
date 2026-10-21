cmake_minimum_required(VERSION 3.14)
project(exemploCpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Cria a biblioteca principal com a classe de parsing e o driver serial
add_library(sensor_core
    src/core.cpp
    src/example.cpp
)
target_include_directories(sensor_core PUBLIC include)

# 2. Cria o executavel principal
add_executable(main_app src/main.cpp)
target_link_libraries(main_app PRIVATE sensor_core)

# 3. Configura os testes unitarios
enable_testing()
add_executable(test_core tests/test_core.cpp)
target_link_libraries(test_core PRIVATE sensor_core)
add_test(NAME TesteMPU6050 COMMAND test_core)