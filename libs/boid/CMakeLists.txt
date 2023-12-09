cmake_minimum_required(VERSION 3.22.1)
project(boid
        VERSION 0.1
        DESCRIPTION "libreria per robotica di gruppo")

add_library(boid STATIC src/boid.cpp)

target_include_directories(boid PUBLIC include)
target_link_libraries(boid PRIVATE X11)

add_library(PSE::boid ALIAS boid)