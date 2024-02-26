cmake_minimum_required(VERSION 3.22.1)
project(homework
        VERSION 0.1
        DESCRIPTION "homework PSE 23-24")

# Create targets for building the (local) libraries.
add_subdirectory(libs/Boid)
# Create the targets for the entire example-app.
add_subdirectory( app )