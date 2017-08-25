#include "ReflectTriangle.h"
#include "Shading.h"

ReflectTriangle::ReflectTriangle(vectors::vec3 a, vectors::vec3 b, vectors::vec3 c):Triangle(a,b,c){}

Color ReflectTriangle::rayInteract(Ray r, double dist, World& w, int recursion){
	return Shading::reflect(r, r.posAtDist(dist-0.01), getNormal(), w, recursion);
}
