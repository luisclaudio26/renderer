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
		
		typedef struct {
			glm::vec3 p, q;
		} AABB;

		class Primitive
		{
		public:
			virtual void intersect(const Ray& r, Intersection& out) = 0;
		};
	}
}

#endif