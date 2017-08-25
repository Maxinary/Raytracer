#pragma once
#include "WorldObject.h"
#include "vectors.h"

class Triangle: public WorldObject{
public:
	Triangle(vectors::vec3 a, vectors::vec3 b, vectors::vec3 c);
	
	double rayTouching(Ray r);
	virtual Color rayInteract(Ray, double, World&, int)=0;
	
	vectors::vec3 getNormal() const;
	
private:
	const vectors::vec3 normal;
	const vectors::vec3 vertices[3];
};
