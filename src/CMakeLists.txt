cmake_minimum_required(VERSION 3.25)
project(raytracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(raytracer main.cpp common_math/vec3.h common_math/ray.h hittable.h primitives/sphere.h hittable_list.h material.h file_writer.h file_writer.cpp common_math/random.h camera.cpp camera.h common_math/vec3.cpp common_math/ray.cpp hittable_list.cpp material.cpp primitives/sphere.cpp interval.cpp interval.h aabb.cpp aabb.h bvh.cpp bvh.h texture.cpp texture.h scenes.cpp scenes.h external/stb_image.h image_wrapper.cpp image_wrapper.h perlin.cpp perlin.h primitives/quad.cpp primitives/quad.h common_math/constants.h common_math/triginometry.h common_math/random.h common_math/other.h primitives/triangle.cpp primitives/triangle.h primitives/placeable_on_plane.cpp primitives/placeable_on_plane.h common_math/mat.cpp common_math/mat.h)
