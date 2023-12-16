cmake_minimum_required(VERSION 3.22.1)

add_executable(eseguibile src/test_storm.cpp)

target_link_libraries(eseguibile
        PRIVATE PSE::boid)