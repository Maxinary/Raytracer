#pragma once

#include "vectors.h"
#include "Ray.h"

class World;
struct Color;

class WorldObject{
public:
	WorldObject(vectors::vec3 pos) : pos(pos){};
	
	virtual double rayTouching(Ray r)=0;
	virtual Color rayInteract(Ray, double, World&, int)=0;

	vectors::vec3 pos;
};
