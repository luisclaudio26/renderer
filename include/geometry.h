#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>

namespace Renderer
{
	namespace Geometry
	{
		class Ray
		{
		public:
			glm::vec3 o; glm::vec3 d;
			glm::vec3 operator()(float t) { return o + d*t; }
		};
	}
}

#endif