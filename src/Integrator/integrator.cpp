#include "../../include/Integrator/integrator.h"

namespace Renderer
{
	namespace Integration
	{
		void Integrator::addCamera(const Camera::ptr& c) { this->cam = c; }
	
		void Integrator::addLight(const Light::ptr& l) { this->lights.push_back(l); }

		void Integrator::addShape(const Shape::ptr& s) { this->shapes.push_back(s); }

		void Integrator::render(const std::string& path) const
		{
			return;
		}
	}
}