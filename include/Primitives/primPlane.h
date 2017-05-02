#ifndef PRIM_PLANE_H
#define PRIM_PLANE_H

#include "primitive.h"

namespace Renderer
{
	namespace Shapes
	{
		class PrimPlane : public Primitive
		{
		public:
			glm::vec3 normal;
			glm::vec4 center;

			PrimPlane(glm::vec3 n, glm::vec4 c);
			PrimPlane();
			
			void intersect(const Ray& r, Intersection& out) override;
			void defineBBox() override;
		};
	}
}

#endif