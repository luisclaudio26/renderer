#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include "Primitives/primitive.h"
#include "intersection.h"

namespace Renderer
{
	namespace Scene
	{
		using namespace Shapes;
		using namespace Geometry;

		class kdNode
		{
		public:
			//AABB bbox;
			kdNode *r, *l;

			//std::vector<TriFace*> triangles;
		};

		class kdTree
		{
		public:
			kdNode root;

			//void build(std::vector<TriFace*>& triangles, int depth);
			//void closestTriangle(const Ray& r, Intersection& out);
		};
	}
}

#endif