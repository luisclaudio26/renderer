#include "../include/scene.h"
#include <iostream>
#include <algorithm>

namespace Renderer
{
	namespace Scene
	{
		using namespace Geometry;

		void SceneManager::addLight(const Light::ptr& l) { this->lights.push_back(l); }
		void SceneManager::addShape(const Shape::ptr& s) { this->shapes.push_back(s); }

		void hit(const kdNode& n, const Ray& r, Intersection& out)
		{
			//assumes out.t = Infinity and out.valid = false
			//in the first call
			float tmin, tmax;
			if( n.bbox.intersect(r, tmin, tmax) )
			{
				//If we reached a leaf...
				if( n.r == NULL && n.l == NULL )
				{
					for(auto p = n.prim.begin(); p != n.prim.end(); ++p)
					{
						Intersection I; (*p)->intersect(r, I);

						//we consider only intersections in the positive direction
						//of the ray; it is useless (in this context) to consider
						//intersection in the negative side! (this implies intersection
						//with things behind the origin of the ray).
						if(I.valid && I.t > 0.0f && I.t < out.t) out = I;
					}
				}
				else
				{
					//intersect with bounding boxes
					hit((*n.l), r, out);
					hit(*(n.r), r, out);
				}
			}
		}

		void SceneManager::shootCameraRay(const Ray& r, Intersection& out) const
		{
			out.t = std::numeric_limits<float>::max();
			out.valid = false;

			hit(tree.root, r, out);
		}

		void SceneManager::buildTree()
		{
			//gather all primitives in scene
			std::vector<Primitive*> prim;
			for(auto s = shapes.begin(); s != shapes.end(); ++s)
				(*s)->getPrimitives(prim);

			//build tree
			tree.build(prim);
		}
	}
}