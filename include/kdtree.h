#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include "Primitives/primitive.h"
#include "intersection.h"
#include <stack>

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
			int axis; float t;
			std::vector<int> primNum;
		};
		
		class kdTree
		{
		private:
			mutable bool tryBackfaceCulling;

		public:
			kdNode root; int maxDepth;
			std::vector<Primitive*> prim;

			kdTree() : maxDepth(-1), tryBackfaceCulling(false) {}

			void build(std::vector<Primitive*>&& prim);
			void hit(const Ray& r, Intersection& out, bool tryBackfaceCulling) const;
			void hit(const kdNode& n, const Ray& r, float tmin, 
						float tmax, Intersection& out) const;

		private:
			void buildNode(kdNode& n, int depth = 0);
		};
	}
}

#endif