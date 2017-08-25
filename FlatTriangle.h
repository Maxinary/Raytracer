#pragma once

#include "Triangle.h"
#include "Color.h"

class FlatTriangle: public Triangle{
public:
	FlatTriangle(vectors::vec3, vectors::vec3, vectors::vec3, Color);
	
	virtual Color rayInteract(Ray, double, World&, int);
	
	Color color;	
};
