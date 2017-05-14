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
			AABB bbox;
			kdNode *r, *l;
			float split;

			std::vector<Primitive*> prim;
		};

		class kdTree
		{
		public:
			kdNode root;

			void build(const std::vector<Primitive*>& prim, int depth);
			void intersect(const Ray& r, Intersection& out);
		};
	}
}

#endif