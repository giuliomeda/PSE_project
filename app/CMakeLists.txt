cmake_minimum_required(VERSION 3.22.1)

add_executable(eseguibile src/test_movement_boid.cpp)

target_link_libraries(eseguibile
        PRIVATE PSE::boid)