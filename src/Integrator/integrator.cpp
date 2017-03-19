#include "../../include/Integrator/integrator.h"
#include "../../include/imageWriter.h"
#include "../../include/geometry.h"

#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Integration
	{
		using Geometry::Ray;

		void Integrator::addCamera(const Camera::ptr& c) { this->cam = c; }
	
		void Integrator::addLight(const Light::ptr& l) { this->lights.push_back(l); }

		void Integrator::addShape(const Shape::ptr& s) { this->shapes.push_back(s); }

		void Integrator::render(const std::string& path) const
		{
			Pixel255* img = new Pixel255[cam->hRes * cam->vRes];
			memset(img, 0, sizeof(Pixel255) * cam->hRes * cam->vRes);

			for(int i = 0; i < cam->hRes; ++i)
				for(int j = 0; j < cam->vRes; ++j)
				{
					//Image space is in range [-1, 1),
					//in both directions. We transform pixels
					//from device coordinates to image coordinates.
					//TODO: correctly sample this
					float u = ((2.0f*i - cam->hRes) / cam->hRes) + 0.5f;
					float v = ((2.0f*j - cam->vRes) / cam->vRes) + 0.5f;

					Ray r; cam->shootRayThrough(u, v, r);
				}

			writePixelsToFile(path.c_str(), cam->hRes, cam->vRes, img);
			delete[] img;
		}
	}
}