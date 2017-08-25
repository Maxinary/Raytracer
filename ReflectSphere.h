#pragma once

#include "Sphere.h"
//#include "vectors.h"
//#include "Colors"

class ReflectSphere: public Sphere{
public:
	ReflectSphere(vectors::vec3, double);
	
	virtual Color rayInteract(Ray, double, World&, int);
};
