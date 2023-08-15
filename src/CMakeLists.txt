cmake_minimum_required(VERSION 3.25)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled1 main.cpp vec3.h color.h ray.h hittable.h sphere.h hittable_list.h common.h camera.h material.h)
