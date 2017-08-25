#pragma once

#include <vector>

#include "WorldObject.h"
#include "Ray.h"
#include "Color.h"
#include "Light.h"

class World{
	public:
		World();
		
		/* add object */
		void addObject(WorldObject* w);
		void addLightSource(Light);
		
		Color processRay(Ray, int);
		
		std::vector<Light> getLights();
		std::vector<WorldObject*> getObjects();

	private:
		std::vector<WorldObject*> objects;
		std::vector<Light> lights;
		const int MAX_REFLECT = 12;
		const Color SKY_COLOR = Color{200,200,240};
};
