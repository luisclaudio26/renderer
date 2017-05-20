#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include <memory>
#include "../scene.h"
#include "../camera.h"
#include "../geometry.h"
#include "../imageWriter.h"
#include "../Spectra/rgbSpectrum.h"

namespace Renderer
{
	using Lighting::Light;
	using Shapes::Shape;
	using Cameras::Camera;
	using Scene::SceneManager;
	using namespace Geometry;

	namespace Integration
	{
		class Integrator
		{
		protected:
			SceneManager::ptr scene;
			Camera::ptr cam;

			virtual void integrate(const Ray& eye2obj, 
									const Intersection& inter, RGBSpectrum& out) const = 0;

		public:
			typedef std::shared_ptr<Integrator> ptr;

			void addCamera(const Camera::ptr& c);
			void addScene(const SceneManager::ptr& s);

			void render(const std::string& path) const;
		};
	}
}

#endif