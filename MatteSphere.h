#pragma once

#include "Sphere.h"
#include "Color.h"


class MatteSphere : public Sphere {
public:
	MatteSphere(vectors::vec3, double, Color);
	
	virtual Color rayInteract(Ray, double, World&, int);
	
	Color color;
};
