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

		bool hit(const kdNode& n, const Ray& r, Intersection& out)
		{
			//assumes out.t = Infinity and out.valid = false
			//in the first call
			bool has_hit = false;

			//If we reached a leaf...
			if( n.r == NULL && n.l == NULL )
			{
				for(auto p = n.prim.begin(); p != n.prim.end(); ++p)
				{
					//TODO: Primitives do not their own material!
					//must fix this.
					Intersection I; (*p)->intersect(r, I);
					if(I.valid && I.t < out.t)
					{
						out = I;
						has_hit = true;
					}
				}
			}
			else
			{
				float tmin, tmax;
				if( n.bbox.intersect(r, tmin, tmax) )
				{
					//intersect with bounding boxes
					bool hitLeft = hit((*n.l), r, out);
					bool hitRight = hit(*(n.r), r, out);

					has_hit = hitLeft || hitRight;
				}
				else 
					has_hit = false;
			}

			return has_hit;
		}

		void SceneManager::shootCameraRay(const Ray& r, Intersection& out) const
		{
			out.t = std::numeric_limits<float>::max();
			out.valid = false;

			bool intersected = hit(tree.root, r, out);

			if(intersected)
			{
				Lambertian *m = new Lambertian; 
				m->color = glm::vec3(1.0f, 0.0f, 0.0f);
				out.material = BRDF::ptr(m);
			}
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