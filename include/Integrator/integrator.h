#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include <memory>
#include "../scene.h"
#include "../camera.h"

namespace Renderer
{
	using Lighting::Light;
	using Shapes::Shape;
	using Cameras::Camera;
	using Scene::SceneManager;

	namespace Integration
	{
		class Integrator
		{
		protected:
			SceneManager::ptr scene;
			Camera::ptr cam;

		public:
			typedef std::unique_ptr<Integrator> ptr;

			void addCamera(const Camera::ptr& c);
			void addScene(const SceneManager::ptr& s);

			void render(const std::string& path) const;
		};
	}
}

#endif