cmake_minimum_required(VERSION 3.17)
project(o_ran)

set(CMAKE_CXX_COMPILER_VERSION 9)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp writer/IWriter.h reader/IReader.h writer/ConsoleWriter.cpp writer/ConsoleWriter.h writer/HTTPWriter.cpp writer/HTTPWriter.h reader/JSONReader.cpp reader/JSONReader.h controller/Controller.cpp controller/Controller.h libs/Random.h)


target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
