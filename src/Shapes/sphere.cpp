#include "../../include/Shapes/sphere.h"
#include <cmath>

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		std::string Sphere::str()
		{
			std::string s("");
			
			s += "[Radius: ";
			s += std::to_string(this->radius);
			s += ", Center: ";
			s += glm::to_string(this->center);
			s += "]";

			return s;
		}

		void Sphere::intersect(const Ray& r, Intersection& out)
		{
			//I don't know where to move this.
			const float EPS = 0.0001;

			glm::vec3 center = glm::vec3(this->center);
			glm::vec3 o = center - r.o;

			float a = glm::dot(r.d, r.d);
			float b = -2.0f * glm::dot(o, r.d);
			float c = glm::dot(o, o);

			//Neither this
			if( fabs(a) < EPS ) 
			{
				out.valid = false;
				return;
			}

			float t1, t2, sq_delta, over_2a;
			sq_delta = sqrt(b*b - 4*a*c);
			over_2a = 1.0f / 2*a;
			t1 = (-b - sq_delta) * over_2a;
			t2 = (-b + sq_delta) * over_2a;

			//if t1 is positive, it is the closest
			//intersection
			if(t1 > EPS)
			{
				out.valid = true;
				out.t = t1;
				out.normal = glm::normalize( r(t1) - center );

				return;
			}

			if(t2 > EPS)
			{
				out.valid = true;
				out.t = t2;
				out.normal = glm::normalize( r(t2) - center );

				return;
			}

			out.valid = false;
		}
	}
}