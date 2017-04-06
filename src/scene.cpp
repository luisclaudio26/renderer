#include "../include/scene.h"
#include <iostream>

namespace Renderer
{
	namespace Scene
	{
		using namespace Geometry;

		void SceneManager::addLight(const Light::ptr& l) { this->lights.push_back(l); }

		void SceneManager::addShape(const Shape::ptr& s) { this->shapes.push_back(s); }

		void SceneManager::shootCameraRay(const Ray& r, Intersection& out) const
		{
			out.t = std::numeric_limits<float>::max();

			for(auto s = shapes.begin(); s != shapes.end(); ++s)
			{
				Intersection I; (*s)->intersect(r, I);
				if(I.valid && I.t < out.t) out = I;
			}
		}
	}
}