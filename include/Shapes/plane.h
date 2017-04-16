#ifndef _PLANE_H_
#define _PLANE_H_

#include "../geometry.h"
#include "shape.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Shapes
	{
		class Plane : public Shape
		{
		public:
			glm::vec3 normal;
			glm::vec4 center;

			void intersect(const Geometry::Ray& r, Intersection& out) override;

			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			std::string str() override;
		};
	}
}

#endif