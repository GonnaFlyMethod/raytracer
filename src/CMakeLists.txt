cmake_minimum_required(VERSION 3.25)
project(raytracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(raytracer main.cpp vec3.h ray.h hittable.h sphere.h hittable_list.h material.h main_helpers.h main_helpers.cpp common_math.h camera.cpp camera.h vec3.cpp ray.cpp hittable_list.cpp material.cpp sphere.cpp interval.cpp interval.h)
