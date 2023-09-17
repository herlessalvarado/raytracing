cmake_minimum_required(VERSION 3.26)
project(raytracing)

set(CMAKE_CXX_STANDARD 17)

find_package(X11 REQUIRED)

add_executable(raytracing
        Camera.cpp
        Camera.h
        CImg.h
        Cylinder.h
        Light.h
        main.cpp
        Object.cpp
        Object.h
        Plane.h
        Ray.cpp
        Ray.h
        Sphere.h
        vec3.cpp
        vec3.h
        World.h)

include_directories(${X11_INCLUDE_DIR})
target_link_libraries(raytracing ${X11_LIBRARIES})