#include <windows.h>
#include <vector>
#include <iostream>

#include "World.h"
#include "MatteSphere.h"
#include "Ray.h"
#include "vectors.h"
#include "Shading.h"

MatteSphere::MatteSphere(vectors::vec3 pos, double radius, Color c) : Sphere(pos, radius), color(c){};

Color MatteSphere::rayInteract(Ray r, double dist, World& w, int rec){
	return 0.05*color+color*Shading::matte(r, r.posAtDist(dist), r.posAtDist(dist)-pos, w);
};
