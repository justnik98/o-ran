cmake_minimum_required(VERSION 3.17)
project(o_ran)

set(CONAN_DISABLE_CHECK_COMPILER)
set(CMAKE_CXX_COMPILER_VERSION 9)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
