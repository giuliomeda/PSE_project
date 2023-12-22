cmake_minimum_required(VERSION 3.22.1)


add_executable(eseguibile src/test_storm.cpp)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

target_link_libraries(eseguibile
        PRIVATE PSE::boid
        ${PYTHON_LIBRARIES})


        