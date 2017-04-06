#include "../../include/Integrator/integrator.h"
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Integration
	{
		using namespace Geometry;

		void Integrator::addCamera(const Camera::ptr& c) { this->cam = c; }
		void Integrator::addScene(const SceneManager::ptr& s) { this->scene = s; }

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

					Ray r; cam->getRay(u, v, r);
					Intersection inter; scene->shootCameraRay(r, inter);

					PixelF p; this->integrate(r, inter, p);
					img[ i*cam->hRes + j ] = pixelFloat2Char(p);
				}

			writePixelsToFile(path.c_str(), cam->hRes, cam->vRes, img);
			delete[] img;
		}
	}
}