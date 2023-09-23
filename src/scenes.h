#pragma once

#include "hittable_list.h"
#include "camera.h"

void random_spheres(HittableList& world, Camera& cam);

void two_spheres_with_checker_texture(HittableList& world, Camera& cam);

void earth(HittableList& world, Camera& cam);

void two_spheres_with_perlin_texture(HittableList& world, Camera& cam);

void quads(HittableList &world, Camera& cam);

void triangle(HittableList& world, Camera& cam);