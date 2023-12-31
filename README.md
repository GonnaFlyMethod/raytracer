# raytracer

This is a raytracer based on the book
[Raytracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).
By implementing the ideas & concepts from the book, I'm teaching myself
how do raytracers work in practice and what underlying principles and math are
used to create cool looking scenes.

Rendered spheres:

![](./collection/rendered_spheres.png)

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

Rendered spheres:

![](./collection/rendered_spheres.png)

Motion blur:

![](./collection/motion_blur.png)

Checker texture:

![](./collection/checker_texture.png)

Earth texture mapping:

![](./collection/earth_texture_mapping.png)

Perlin texture(noise version):

![](./collection/perlin_texture.png)

Perlin texture(gradient version) with turbulence and sin(x) phases:
![](./collection/perlin_noise_gradient_with_phases_texture.png)

Quads:
![](./collection/quads.png)

Triangles:
![](./collection/triangles_with_textures.png)
