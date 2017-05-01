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

			#pragma omp parallel for
			for(int i = 0; i < cam->vRes; ++i)
				for(int j = 0; j < cam->hRes; ++j)
				{
					//Image space is in range [-1, 1),
					//in both directions. We transform pixels
					//from device coordinates to image coordinates.
					//We must invert V coordinates because pixel [0,0]
					//is in top-left corner of the image.
					//TODO: correctly sample this
					float u = 2.0f*(j - cam->hRes * 0.5f) / cam->hRes;
					float v = 2.0f*(cam->vRes * 0.5f - i) / cam->vRes;

					Ray r; cam->getRay(u, v, r);
					Intersection inter; scene->shootCameraRay(r, inter);

					//TODO: Create a base class Spectrum, which has a
					//method .rgb()
					RGBSpectrum p; this->integrate(r, inter, p);
					Pixel255& out = img[ i*cam->hRes + j ];
					out.r = (unsigned char)(p.r*255);
					out.g = (unsigned char)(p.g*255);
					out.b = (unsigned char)(p.b*255);
				}

			writePixelsToFile(path.c_str(), cam->hRes, cam->vRes, img);
			delete[] img;
		}
	}
}