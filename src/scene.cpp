#include "../include/scene.h"
#include <iostream>

namespace Renderer
{
	namespace Scene
	{
		using namespace Geometry;

		void SceneManager::addLight(const Light::ptr& l) { this->lights.push_back(l); }
		void SceneManager::addShape(const Shape::ptr& s) { this->shapes.push_back(s); }

		bool intersectRayPlane(const glm::vec3& center, const glm::vec3& normal, 
								const Ray& r, float& t)
		{
			float d_N = glm::dot(normal, r.d);

			if(fabs(d_N) < 0.00001) return false;
			
			t = glm::dot(normal, center - r.o) / d_N;
			
			return t >= 0.0f;
		}

		bool hit(const kdNode& n, const Ray& r, Intersection& out, int axle = 0)
		{
			//assumes out.t = Infinity and out.valid = false
			//in the first call
			bool has_hit = false;

			//If we reached a leaf...
			if( n.split != n.split )
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
				bool testFar = true;

				//Define Near and Far box
				kdNode *near, *far;
				if( r.o[axle] < n.split ) {
					near = n.l; far = n.r;
				} else {
					near = n.r; far = n.l; 
				}

				//Intersect with splitting plane
				float t_split;
				glm::vec3 center = n.bbox.q, normal = glm::vec3(0.0f, 0.0f, 0.0f);
				center[axle] = n.split; normal[axle] = 1.0f;

				//First test: if ray is parallel to split plane, it wont
				//intersect the Far-box.
				testFar = !intersectRayPlane(center, normal, r, t_split);

				glm::vec3 inter = r(t_split);

				//Second test: if intersection with split plane is outside
				//the bounding box, skip far box.
				for(int i = 0; i < 3; i++)
				{
					if(i == axle) continue;

					if(inter[i] > n.bbox.p[i] || inter[i] < n.bbox.q[i])
						testFar = false;
				}

				//We must always test Near-box!
				int nextAxle = (axle + 1) % 3;
				has_hit = hit(*near, r, out, nextAxle);
				
				//if we had intersection with Near-box,
				//skip Far-box.
				if(has_hit) return true;

				if(testFar) has_hit = hit(*far, r, out, nextAxle);
			}

			return has_hit;
		}

		void SceneManager::shootCameraRay(const Ray& r, Intersection& out) const
		{
			out.t = std::numeric_limits<float>::max();
			out.valid = false;
			
			Lambertian *m = new Lambertian; 
			m->color = glm::vec3(1.0f, 0.0f, 0.0f);
			out.material = BRDF::ptr(m);

			hit(tree.root, r, out);

			/*
			for(auto s = shapes.begin(); s != shapes.end(); ++s)
			{
				Intersection I; (*s)->intersect(r, I);
				if(I.valid && I.t < out.t) out = I;
			}
			*/
		}

		void SceneManager::buildTree()
		{
			//gather all primitives in scene
			std::vector<Primitive*> prim;
			for(auto s = shapes.begin(); s != shapes.end(); ++s)
				(*s)->getPrimitives(prim);

			//build tree
			tree.build(prim, 0);
		}
	}
}