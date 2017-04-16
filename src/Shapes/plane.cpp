#include "../../include/Shapes/plane.h"
#include <cmath>
#include <iostream>

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		std::string Plane::str()
		{
			std::string s("");
			
			s += "[Normal: ";
			s += glm::to_string(this->normal);
			s += ", Center: ";
			s += glm::to_string(this->center);
			s += ", Material: ";
			s += this->material->str();
			s += "]";

			return s;
		}

		void Plane::intersect(const Ray& r, Intersection& out)
		{
			float d_N = glm::dot(normal, r.d);

			if( fabs(d_N) < 0.00001 )
			{
				out.valid = false;
				return;
			}
			
			out.t = glm::dot(normal, glm::vec3(center) - r.o) / d_N;

			if(out.t <= 0.0f) {
				out.valid = false;
				return;
			}

			out.valid = true;
			out.normal = normal;
			out.material = material;

			return;
		}
	}
}