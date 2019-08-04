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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/kevin/.local/lib/cmake/opencv4)
set(OpenCV_DIR /home/kevin/.local/lib/cmake/opencv4)

find_package(PkgConfig)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS ">> OpenCV found: ${OpenCV_VERSION}")
    list(APPEND ALL_LIBS ${OpenCV_LIBS})
else()
    message(WARNING "*** Could not find OpenCV ***")
endif()

link_directories(
    ../gecko/build/
    ../gecko/build/extlibs/marko
)

add_executable(camera src/camera.cpp)
target_include_directories(camera
    PUBLIC
        ../gecko/src
)
target_link_libraries(camera
    PUBLIC
        gecko
        ${OpenCV_LIBS}
)
