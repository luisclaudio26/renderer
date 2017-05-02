#include "../include/kdtree.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <cfloat>

namespace Renderer
{
	namespace Scene
	{
		
		void kdTree::build(const std::vector<Primitive*>& prim, int depth)
		{
			//find bounding box for the whole scene

			//launch kd tree building method for root node
		}

		void kdTree::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;
		}
	}
}