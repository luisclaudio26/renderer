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

		typedef struct {
			const kdNode* n;
			float tmin, tmax;
		} NodeToDo;

		class kdTree
		{
		private:
			mutable std::stack<NodeToDo> stack;

		public:
			kdNode root; int maxDepth;
			std::vector<Primitive*> prim;

			kdTree() : maxDepth(-1) {}

			void build(std::vector<Primitive*>&& prim);
			void hit(const Ray& r, Intersection& out) const;
			void hit(const kdNode& n, const Ray& r, float tmin, 
						float tmax, Intersection& out) const;

		private:
			void buildNode(kdNode& n, int depth = 0);
		};
	}
}

#endif