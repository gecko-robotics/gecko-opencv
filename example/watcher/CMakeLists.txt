cmake_minimum_required(VERSION 3.10.0)
project(gecko-camera)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_host_system_information(RESULT HOST QUERY HOSTNAME)
# cmake_host_system_information(RESULT CORES QUERY NUMBER_OF_LOGICAL_CORES)
cmake_host_system_information(RESULT OSN QUERY OS_NAME)
cmake_host_system_information(RESULT OS_VERSION QUERY OS_RELEASE)
cmake_host_system_information(RESULT PROC QUERY PROCESSOR_DESCRIPTION)

message(STATUS "-------------------------------------")
message(STATUS "  Project: ${PROJECT_NAME}")
message(STATUS "  C++ ${CMAKE_CXX_STANDARD}")
message(STATUS "-------------------------------------")
message(STATUS " ${HOST}")
message(STATUS " ${OSN}: ${OS_VERSION}")
message(STATUS " ${PROC}")
message(STATUS "-------------------------------------")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/kevin/.local/lib/cmake/opencv4)


find_package(PkgConfig)

# OpenCV --------------------------------------------------------------
if(NOT APPLE)
    set(OpenCV_DIR /home/kevin/.local/lib/cmake/opencv4)
    set(MessagePack_DIR /home/kevin/.local/lib/cmake/msgpack)
endif()

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS ">> OpenCV found: ${OpenCV_VERSION}")
else()
    message(WARNING "*** Could not find OpenCV ***")
endif()

# ZeroMQ -------------------------------------------------------------
pkg_check_modules(libzmq REQUIRED libzmq)
if(libzmq_FOUND)
    message(STATUS ">> ZeroMQ found: ${libzmq_VERSION}")
    # option(ZMQ_BUILD_DRAFT_API " " OFF)
else()
    message(WARNING "*** Could not find ZeroMQ ***")
endif()

# Source ----------------------------------------------------------------
list(APPEND sources
    watcher.cpp
)

foreach(src ${sources})
    get_filename_component(name ${src} NAME_WE)
    message(STATUS " -> ${name}")

    add_executable(${name} ${src})
    target_include_directories(${name}
        PUBLIC
            ${libzmq_INCLUDE_DIRS}
            ../../../gecko/src
            ../../../gecko/extlibs/gecko-msgpack
            ../../../gecko/extlibs/cppzmq
            ../../../gecko/extlibs/marko/lib/include
            ../../../gecko/extlibs/nlohmann-json/include
            /usr/local/include
    )
    target_link_libraries(${name}
        PUBLIC
            gecko
            ${OpenCV_LIBS}
            ${libzmq_LIBRARIES}
    )
    target_link_directories(${name}
        PUBLIC
            ../../../gecko/build/
            ../../../gecko/build/extlibs/marko
            /usr/local/lib
    )
endforeach()
