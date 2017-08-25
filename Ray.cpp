#include "Ray.h"

Ray::Ray():pos(vectors::vec3(0,0,0)),direction(vectors::vec3(0,0,0)){}

Ray::Ray(const vectors::vec3 pos, const vectors::vec3 direction) : pos(pos), direction(direction){}

vectors::vec3 Ray::posAtDist(double dist){
	return vectors::vec3(pos.x+direction.x*dist, pos.y+direction.y*dist, pos.z+direction.z*dist);
}
