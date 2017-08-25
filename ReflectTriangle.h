#pragma once

#include "Triangle.h"
#include "Color.h"

class ReflectTriangle: public Triangle{
public:
	ReflectTriangle(vectors::vec3, vectors::vec3, vectors::vec3);
	
	Color rayInteract(Ray, double, World&, int);
};
