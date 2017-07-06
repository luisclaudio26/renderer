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
			Ray operator=(const Ray& r) { o = r.o; d = r.d; return *this; }
		};

		typedef struct {
			glm::vec3 min, max;
			bool intersect(const Ray& r, float& t_min, float& t_max) const;
			int maximumExtent() const;
		} AABB;
	}
}

#endif