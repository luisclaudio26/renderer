#include "../include/camera.h"
#include <cmath>

namespace Renderer
{
	namespace Cameras
	{
		using Geometry::Ray;

		void Camera::shootRayThrough(float u, float v, Ray& out)
		{
			//These width and height values have (a priori) nothing
			//to do with the actual width and height of the final image!
			//These are the dimensions of the film in camera space.
			const float w = this->d * tan(this->FOV * 0.5f);
			const float h = w / this->aspectRatio;

			//Mapping the range [-1,1) to [-w/2, w/2)
			//(and [-h/2, h/2) ). This maps our <u,v>
			//pixel from image space to camera space.
			float x = u * w * 0.5f, y = v * h * 0.5f;

			//Transform ray from camera space to world space
			//[p,q,r] will be mapped to canonical [x,y,z] space.
			glm::vec3 p, q, r;
			r = look - pos;
			q = up - glm::dot(up, r)*r;
			p = glm::cross(q, r);

			glm::mat3 world2cam(p, q, r);
			glm::mat3 cam2world = glm::inverse(world2cam);

			out.d = cam2world * glm::vec3(-d, x, y);
			out.o = pos;
		}

		Camera::ptr Camera::cameraFromJSON(const nlohmann::json& in)
		{
			//TODO: in the future, we shall create different cameras
			//(ortographics, projective) depending on the parameters.
			ptr out(new Camera);

			out->pos = JSONHelper::vec3FromJSON(in["pos"]);
			out->up = JSONHelper::vec3FromJSON( in["up"] );
			out->look = JSONHelper::vec3FromJSON( in["look"] );

			out->w = in["width"].get<int>();
			out->h = in["height"].get<int>();
			out->samplesPerPixel = in["samplesPerPixel"].get<int>();
			out->FOV = in["FOV"].get<float>();
			out->aspectRatio = in["aspectRatio"].get<float>();
			out->d = in["filmDistance"].get<float>();

			return out;
		}
	}
}