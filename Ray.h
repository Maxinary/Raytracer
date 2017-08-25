#pragma once

#include "vectors.h"

class Ray{
public:
	Ray();
	Ray(const vectors::vec3 pos, const vectors::vec3 direction);
	/* No pointers, using default destructor */
	
	vectors::vec3 posAtDist(double dist);
	
	vectors::vec3 pos, direction;
};
