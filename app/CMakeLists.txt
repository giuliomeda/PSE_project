cmake_minimum_required(VERSION 3.22.1)


add_executable(eseguibile src/main.cpp)

target_link_libraries(eseguibile
        PRIVATE PSE::Boid
        ${PYTHON_LIBRARIES})


        