#include "FlatSphere.h"

FlatSphere::FlatSphere(vectors::vec3 pos, double radius, Color c) : Sphere(pos, radius), color(c){};

Color FlatSphere::rayInteract(Ray r, double dist, World& w, int i){
	return color;
};
