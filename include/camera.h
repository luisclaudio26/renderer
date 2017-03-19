#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "jsonHelper.h"
#include "geometry.h"

namespace Renderer
{
	namespace Cameras
	{
		class Camera
		{
		public:
			typedef std::shared_ptr<Camera> ptr;

			glm::vec3 pos;
			glm::vec3 up, look;

			float aspectRatio, FOV;
			int w, h, d; //width, height, distance between image plane and camera center
			int samplesPerPixel;

			void shootRayThrough(float u, float v, Geometry::Ray& out);

			static ptr cameraFromJSON(const nlohmann::json& in);
		};
	}
}

#endif