#ifndef _PLANE_H_
#define _PLANE_H_

#include "../geometry.h"
#include "shape.h"
#include "../Primitives/primPlane.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Shapes
	{
		class Plane : public Shape
		{
		public:
			PrimPlane p;

			void intersect(const Geometry::Ray& r, Intersection& out) override;

			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			std::string str() override;
		};
	}
}

#endif