#include "Shading.h"

Color Shading::flat(Ray r, vectors::vec3 pos, vectors::vec3 normal, World& w){
	return Color{255,255,255};
}

Color Shading::matte(Ray r, vectors::vec3 pos, vectors::vec3 normal, World& w){
	Color c{0,0,0};
	std::vector<Light> lights = w.getLights();
	vectors::vec3 hitPoint = pos;
	for(std::vector<Light>::iterator it = lights.begin(); it != lights.end(); it++){
		double lightPercent = (((*it).pos-hitPoint).normalize().dot(normal));
		if(lightPercent>0){
			Color amount = (*it).color*(lightPercent*(*it).intensity);
			c = c+amount;
		}
	}
	return c;
}

Color Shading::reflect(Ray r, vectors::vec3 pos, vectors::vec3 normal, World& w, int rec){
	return w.processRay(Ray(pos, r.direction-(normal.scale(2*r.direction.dot(normal)))), rec+1);
	/**/
}

