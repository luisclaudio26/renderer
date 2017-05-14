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

		bool intersectRayPlane(const glm::vec3& center, const glm::vec3& normal, 
								const Ray& r, float& t)
		{
			float d_N = glm::dot(normal, r.d);
			if(fabs(d_N) < 0.00001) return false;
			
			t = glm::dot(normal, center - r.o) / d_N;
			
			return t >= 0.0f;
		}

		bool intersectRayBBox(const Ray& r, const AABB& bbox, float& t_min, float& t_max)
		{
			//Taken from 
			//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
			//TODO: modify code so it uses max/min, which is faster.
			float tmin = (bbox.q[0] - r.o[0]) / r.d[0];
			float tmax = (bbox.p[0] - r.o[0]) / r.d[0];

			if (tmin > tmax) std::swap(tmin, tmax);

			float tymin = (bbox.q[1] - r.o[1]) / r.d[1];
			float tymax = (bbox.p[1] - r.o[1]) / r.d[1];

			if (tymin > tymax) std::swap(tymin, tymax);

			if ((tmin > tymax) || (tymin > tmax)) return false;

			if (tymin > tmin)
				tmin = tymin;

			if (tymax < tmax)
				tmax = tymax;

			float tzmin = (bbox.q[2] - r.o[2]) / r.d[2];
			float tzmax = (bbox.p[2] - r.o[2]) / r.d[2];

			if (tzmin > tzmax) std::swap(tzmin, tzmax);

			if ((tmin > tzmax) || (tzmin > tmax)) return false;

			if (tzmin > tmin)
				tmin = tzmin;

			if (tzmax < tmax)
				tmax = tzmax;

			return true; 
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
				float tmin, tmax;
				if( intersectRayBBox(r, n.bbox, tmin, tmax) )
				{
					int nextAxle = (axle + 1) % 3;

					//intersect with bounding boxes
					bool hitLeft = hit((*n.l), r, out, nextAxle);
					bool hitRight = hit(*(n.r), r, out, nextAxle);

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
				m->color = glm::vec3(1.0f, 1.0f, 1.0f);
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
			tree.build(prim, 0);
		}
	}
}