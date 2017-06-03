#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../geometry.h"
#include "../intersection.h"
#include <glm/glm.hpp>

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;
		
		class Primitive
		{
		public:
			AABB bbox;
			BRDF::ptr material;
			
			virtual void defineBBox() = 0;
			virtual void intersect(const Ray& r, Intersection& out, bool tryBackfaceCulling = false) = 0;
		};
	}
}

#endif