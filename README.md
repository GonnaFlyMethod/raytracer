# raytracer

This is a raytracer based on the book
[Raytracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).
By implementing the ideas & concepts from the book, I'm teaching myself
how do raytracers work in practice and what underlying principles and math are
used to create cool looking scenes.

Final result:

![](./collection/final_result.png)

# Building the project
This project uses cmake as a build system. `CMakeLists.txt` should be utilized to generate cmake-related directory. For example, CLion IDE offers to pick the path to `CMakeLists.txt`
at the beginning of work:
![](./collection/cmake_instructions.png)
![](./collection/cmake_instructions1.png)

`CMakeLists.txt` is located in `src/CMakeLists.txt`


Evolution of my journey:

A scene without antialiasing:

![](./collection/no_antialiasing.png)

Antialiasing upper right neighbours:

![](./collection/antialiasing_upper_right_pixels.png)

Antialiasing all neighbour pixels:

![](./collection/antialiasing_all_neighbour_pixels.png)

Diffuse materials gamma correction:

![](./collection/diffuse_materials_gamma_correction.png)

Hemispherical scattering:

![](./collection/hemispherical_scattering.png)

True lambertian reflection:

![](./collection/true_lambertian_reflection.png)

Metal with lambertian:

![](./collection/metal_with_lambertian.png)

Fuzzed metal:

![](./collection/fuzzed_metal.png)

Depth of field effect:

![](./collection/dof_effect.png)

Motion blur:

![](./collection/motion_blur.png)

Texture Mapping

![](./collection/texture_mapping.png)

Final result:

![](./collection/final_result.png)
