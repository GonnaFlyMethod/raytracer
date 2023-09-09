cmake_minimum_required(VERSION 3.25)
project(raytracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(raytracer main.cpp vec3.h ray.h hittable.h sphere.h hittable_list.h material.h file_writer.h file_writer.cpp common_math.h camera.cpp camera.h vec3.cpp ray.cpp hittable_list.cpp material.cpp sphere.cpp interval.cpp interval.h aabb.cpp aabb.h bvh.cpp bvh.h texture.cpp texture.h scenes.cpp scenes.h external/stb_image.h image_wrapper.cpp image_wrapper.h perlin.cpp perlin.h)
