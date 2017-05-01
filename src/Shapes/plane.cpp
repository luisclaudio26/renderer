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
			s += glm::to_string(this->p.normal);
			s += ", Center: ";
			s += glm::to_string(this->p.center);
			s += ", Material: ";
			s += this->material->str();
			s += "]";

			return s;
		}

		void Plane::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;
			Intersection I; p.intersect(r, I);
			if(I.valid)
			{
				out = I;
				out.material = material;
			}
		}
	}
}