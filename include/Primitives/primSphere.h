#ifndef PRIM_SPHERE_H
#define PRIM_SPHERE_H

#include "primitive.h"

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		class PrimSphere : public Primitive
		{
		public:
			double radius;
			glm::vec4 center;

			void intersect(const Ray& r, Intersection& out) override;
			void defineBBox() override;
		};
	}
}

#endif