#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include <memory>
#include "../Lights/light.h"
#include "../Shapes/shape.h"
#include "../camera.h"

namespace Renderer
{
	using Lighting::Light;
	using Shapes::Shape;
	using Cameras::Camera;

	namespace Integration
	{
		class Integrator
		{
		protected:
			std::vector<Light::ptr> lights;
			std::vector<Shape::ptr> shapes;
			Camera::ptr cam;

		public:
			typedef std::unique_ptr<Integrator> ptr;

			void addCamera(const Camera::ptr& c);
			void addLight(const Light::ptr& l);
			void addShape(const Shape::ptr& s);

			void render(const std::string& path) const;
		};
	}
}

#endif