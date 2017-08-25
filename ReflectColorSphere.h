#pragma once

#include "ReflectSphere.h"
#include "Color.h"
class ReflectColorSphere: public ReflectSphere{
public:
	ReflectColorSphere(vectors::vec3, double, Color);
	
	virtual Color rayInteract(Ray, double, World&, int);
	
	Color color;
};
