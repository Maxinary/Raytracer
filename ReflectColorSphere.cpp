#include "ReflectColorSphere.h"
#include "Shading.h"
#include "Ray.h"

ReflectColorSphere::ReflectColorSphere(vectors::vec3 v, double r, Color c):ReflectSphere(v,r),color(c){}

Color ReflectColorSphere::rayInteract(Ray r, double d, World& w, int rec){
	return color*0.2+color*Shading::reflect(r, r.posAtDist(d),r.posAtDist(d)-pos, w, rec);
}

