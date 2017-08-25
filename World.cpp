#include "World.h"

#include <iterator>

World::World(){
};

void World::addObject(WorldObject* w){
	objects.push_back(w);
}

void World::addLightSource(Light v){
	lights.push_back(v);
}

Color World::processRay(Ray r, int recursionCount){
	if(recursionCount < MAX_REFLECT){
		if(recursionCount != 0){
			recursionCount;
		}
		double dist = -1;
		WorldObject* index = nullptr;
		for(std::vector<WorldObject*>::iterator it = objects.begin(); it != objects.end(); it++){
			double d = (*it)->rayTouching(r);
			if(d > 0 && (d < dist || dist < 0)){
				dist = d;
				index = *it;
			}
		}
		if(index != nullptr){
			return index->rayInteract(r, dist, *this, recursionCount);
		}else{
			return SKY_COLOR;
		}
	}else{
		return SKY_COLOR;
	}
}

std::vector<Light> World::getLights(){
	return this->lights;
}

std::vector<WorldObject*> World::getObjects(){
	return this->objects;
}
