#pragma once

#include "Sphere.h"
#include "Color.h"

class FlatSphere : public Sphere {
public:
	FlatSphere(vectors::vec3, double, Color);
	
	virtual Color rayInteract(Ray, double, World&, int);
	
	Color color;
};
