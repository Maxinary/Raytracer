#pragma once
#include "Color.h"
#include "vectors.h"
#include "Light.h"
#include "World.h"
#include "Ray.h"
#include <vector>

namespace Shading{
	Color flat(Ray r, vectors::vec3, vectors::vec3 normal, World& w);
	
	Color matte(Ray r, vectors::vec3, vectors::vec3 normal, World& w);

	Color reflect(Ray r, vectors::vec3, vectors::vec3 normal, World& w, int rec);
}
