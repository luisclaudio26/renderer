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
			//std::vector<Primitive*> prim;
			std::vector<int> primNum;
		};

		class kdTree
		{
		public:
			kdNode root; int maxDepth;
			std::vector<Primitive*> prim;

			kdTree() : maxDepth(-1) {}
			
			void build(std::vector<Primitive*>&& prim);
			void hit(const kdNode& n, const Ray& r, Intersection& out) const;

		private:
			void buildNode(kdNode& n, int depth = 0);
		};
	}
}

#endif