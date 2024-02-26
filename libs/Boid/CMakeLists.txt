cmake_minimum_required(VERSION 3.22.1)
project(Boid
        VERSION 0.1
        DESCRIPTION "libreria per robotica di gruppo")

add_library(Boid STATIC src/Boid.cpp
                        src/Boids_manager.cpp)

target_include_directories(Boid PUBLIC include)

add_library(PSE::Boid ALIAS Boid)