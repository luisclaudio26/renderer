#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <string>
#include "Shapes/shape.h"
#include "Lights/light.h"
#include "geometry.h"

namespace Renderer
{
	namespace Scene
	{
		using Lighting::Light;
		using Shapes::Shape;

		class SceneManager
		{
		public:
			typedef std::shared_ptr<SceneManager> ptr;
			
			std::vector<Light::ptr> lights;
			std::vector<Shape::ptr> shapes;

			void addLight(const Light::ptr& l);
			void addShape(const Shape::ptr& s);

			void shootCameraRay(const Geometry::Ray& r, Intersection& out) const;
		};
	}
}

#endif