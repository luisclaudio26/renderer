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
			
			s += "[Plane]";

			return s;
		}

		void Plane::getPrimitives(std::vector<Primitive*>& out)
		{
			out.push_back(&this->bl);
			out.push_back(&this->ur);
		}

		void Plane::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;

			Intersection iBL, iUR;
			iBL.t = iUR.t = std::numeric_limits<float>::max();

			bl.intersect(r, iBL);
			ur.intersect(r, iUR);

			//Unless we hit the exact border between two
			//triangles, we'll never have two intersections.
			//TODO: this has already happened once, but seemed
			//to cause no problem
			if(iBL.valid) out = iBL;
			else if(iUR.valid) out = iUR;
		}
	}
}