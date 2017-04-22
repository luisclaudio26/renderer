#include "../include/camera.h"
#include <cmath>

namespace Renderer
{
	namespace Cameras
	{
		using Geometry::Ray;

		void Camera::getRay(float u, float v, Ray& out)
		{
			//Mapping the range [-1,1) to [-w/2, w/2)
			//(and [-h/2, h/2) ). This maps our <u,v>
			//pixel from image space to camera space.
			float x = u * w * 0.5f, y = v * h * 0.5f;

			//Transform ray from camera space to world space
			//[p,q,r] will be mapped to canonical [x,y,z] space.
			//We invert X coordinate because negative values of
			//X in image space will be mapped to positive values
			//of Z in camera space.
			out.d = glm::normalize(cam2world * glm::vec3(-d, y, -x));
			out.o = cam2world * pos;
		}

		Camera::ptr Camera::cameraFromJSON(const nlohmann::json& in)
		{
			//TODO: in the future, we shall create different cameras
			//(ortographics, projective) depending on the parameters.
			glm::vec3 pos = JSONHelper::vec3FromJSON(in["pos"]);
			glm::vec3 up = JSONHelper::vec3FromJSON( in["up"] );
			glm::vec3 look = JSONHelper::vec3FromJSON( in["look"] );
			int w = in["width"].get<int>();
			int h = in["height"].get<int>();
			float FOV = in["FOV"].get<float>();
			float aspectRatio = in["aspectRatio"].get<float>();
			float d = in["filmDistance"].get<float>();

			Camera* out = new Camera(pos, up, look, aspectRatio, FOV, d, w, h);
			return Camera::ptr(out);
		}
	}
}