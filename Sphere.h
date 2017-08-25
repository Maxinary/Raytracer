#pragma once

#include "WorldObject.h"

class Sphere: public WorldObject{
public:
	Sphere(vectors::vec3, double);

	double rayTouching(Ray r);
	virtual Color rayInteract(Ray, double, World&, int)=0;

	double radius;
};
