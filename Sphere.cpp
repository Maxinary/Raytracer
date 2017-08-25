#include "Sphere.h"
#include <math.h>

Sphere::Sphere(vectors::vec3 pos, double rad) : WorldObject(pos), radius(rad){}

double Sphere::rayTouching(Ray r){
	vectors::vec3 relativeDist = r.pos-pos;
	double sq1 = r.direction.dot(relativeDist);
	double absRelDist = relativeDist.length();
	
	double underRoot = sq1*sq1 - absRelDist*absRelDist + radius*radius;
	
	if(underRoot >= 0){
		double ro = sqrt(underRoot);
		return -sq1>ro?-sq1-ro:-sq1+ro;
	}else{
		return -1;
	}
}


