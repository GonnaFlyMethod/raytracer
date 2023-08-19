cmake_minimum_required(VERSION 3.25)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled1 main.cpp vec3.h ray.h hittable.h sphere.h hittable_list.h material.h main_helpers.h main_helpers.cpp common_math.h camera.cpp camera.h)
