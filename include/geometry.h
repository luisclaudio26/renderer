#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <string>

namespace Renderer
{
	namespace Geometry
	{
		//TODO: Maybe this is not really
		//"geometric" stuff and should be
		//moved to another place.
		typedef struct _inter
		{
			bool valid;
			float t;
			glm::vec3 normal;

			void operator=(const _inter& lhs);
			std::string str();
		} Intersection;

		class Ray
		{
		public:
			glm::vec3 o; glm::vec3 d;
			glm::vec3 operator()(float t) const { return o + d*t; }
		};
	}
}

#endif