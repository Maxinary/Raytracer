#include "FlatTriangle.h"

FlatTriangle::FlatTriangle(vectors::vec3 a, vectors::vec3 b, vectors::vec3 c, Color co) : Triangle(a,b,c), color(co){};

Color FlatTriangle::rayInteract(Ray r, double dist, World& w, int i){
	return color;
};
