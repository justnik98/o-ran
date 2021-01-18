cmake_minimum_required(VERSION 3.17)
project(o_ran)

set(CMAKE_CXX_STANDARD 20)

if (HIREDIS)
    set(HAVE_HIREDIS 1 CACHE INTERNAL HAVE_HIREDIS)
    include_directories(${HIREDIS}/include)
    link_directories(${HIREDIS}/lib)
else ()
    # hiredis.h
    find_path(
            HIREDIS_INCLUDE
            NAMES
            hiredis.h
            PATHS
            /usr/local/hiredis/include/hiredis
            /usr/include
            /usr/local/include/hiredis/
            /usr/local/thirdparty/hiredis/include/hiredis
            ${CMAKE_INSTALL_PREFIX}/include/hiredis
            NO_DEFAULT_PATH
    )
    # libhiredis.a
    find_path(
            HIREDIS_LIB
            NAMES
            libhiredis.a
            PATHS
            /usr/local/lib/
            /usr/local/hiredis/lib
            /usr/lib
            /usr/local/thirdparty/hiredis/lib
            ${CMAKE_INSTALL_PREFIX}/lib
            NO_DEFAULT_PATH
    )

    if ("${HIREDIS_INCLUDE}" STREQUAL "HIREDIS_INCLUDE-NOTFOUND" OR "${HIREDIS_LIB}" STREQUAL "HIREDIS_INCLUDE-NOTFOUND")
        message("${Red}`hiredis` not installed${ColourReset}")
        set(HAVE_HIREDIS 0 CACHE INTERNAL HAVE_HIREDIS)
        include_directories(${CMAKE_INSTALL_PREFIX}/include)
        link_directories(${CMAKE_INSTALL_PREFIX}/lib)
    else ()
        message("${Yellow}Found `hiredis` at ${HIREDIS_LIB} [libhiredis.a] and ${HIREDIS_INCLUDE}/include [hiredis.h] ${ColourReset}")
        set(HAVE_HIREDIS 1 CACHE INTERNAL HAVE_HIREDIS)
        include_directories(${HIREDIS_INCLUDE}/..)
        link_directories(${HIREDIS_LIB})
    endif ()
endif ()

add_library(libs STATIC IMPORTED)
set_target_properties(libs PROPERTIES
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/librandom.a"
        )

add_executable(o_ran main.cpp writer/IWriter.h reader/IReader.h writer/ConsoleWriter.cpp writer/ConsoleWriter.h writer/HTTPWriter.cpp writer/HTTPWriter.h reader/JSONReader.cpp reader/JSONReader.h controller/Controller.cpp controller/Controller.h libs/Random.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(o_ran PRIVATE Threads::Threads libs)
target_link_libraries(o_ran PUBLIC "${HIREDIS_LIB}/libhiredis.a")