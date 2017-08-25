#include "ReflectSphere.h"
#include "Shading.h"

ReflectSphere::ReflectSphere(vectors::vec3 pos, double radius) : Sphere(pos, radius){};

Color ReflectSphere::rayInteract(Ray r, double dist, World& w, int rec){
	return Color{20,30,20}+Shading::reflect(r, r.posAtDist(dist-0.01),r.posAtDist(dist)-pos, w, rec);
};
