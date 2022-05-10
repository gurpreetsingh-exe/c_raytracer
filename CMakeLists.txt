cmake_minimum_required(VERSION 3.7)
project(raytracer VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread -Wall -lm")

set(SOURCES
    src/main.c
    src/vec3.c
    src/ray.c
    src/hitinfo.c)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(raytracer ${SOURCES})

