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

		void SceneManager::shootCameraRay(const Ray& r, Intersection& out) const
		{
			out.t = std::numeric_limits<float>::max();
			out.valid = false;

			tree.hit(r, out);
		}

		void SceneManager::buildTree()
		{
			//gather all primitives in scene
			std::vector<Primitive*> prim;
			for(auto s = shapes.begin(); s != shapes.end(); ++s)
				(*s)->getPrimitives(prim);

			//build tree. We move the PRIM vector
			//because it won't be needed in this
			//function, and we avoid copying it
			//to the Tree structure.
			tree.build( std::move(prim) );
		}
	}
}