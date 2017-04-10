#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <string>

namespace Renderer
{
	namespace Geometry
	{
		class Ray
		{
		public:
			Ray(): o(glm::vec3(0,0,0)), d(glm::vec3(0,0,0)) {  }
			Ray(const glm::vec3& o, const glm::vec3& d) : o(o), d(d) { }

			glm::vec3 o; glm::vec3 d;
			glm::vec3 operator()(float t) const { return o + d*t; }
			Ray operator-() const { return Ray(o, -d); }
		};
	}
}

#endif