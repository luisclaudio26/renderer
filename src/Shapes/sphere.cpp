#include "../../include/Shapes/sphere.h"
#include <cmath>

#include <iostream>

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		std::string Sphere::str()
		{
			std::string s("");
			
			s += "[Radius: ";
			s += std::to_string(this->s.radius);
			s += ", Center: ";
			s += glm::to_string(this->s.center);
			s += "]";

			return s;
		}

		void Sphere::getPrimitives(std::vector<Primitive*>& out)
		{
			out.push_back(&this->s);
		}

		void Sphere::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;
			
			Intersection I; s.intersect(r, I);
			if(I.valid) out = I;
		}
	}
}