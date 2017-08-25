#pragma once

#include "vectors.h"
#include "Color.h"

class Light{
public:
	Light(vectors::vec3, Color, double);
	
	vectors::vec3 pos;
	Color color;
	double intensity;
};
