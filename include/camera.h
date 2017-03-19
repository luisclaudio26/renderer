#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "jsonHelper.h"

namespace Renderer
{
	namespace Cameras
	{
		class Camera
		{
		public:
			typedef std::unique_ptr<Camera> ptr;


			glm::vec4 pos;
			glm::vec3 up, look;

			double aspectRatio, FOV;
			int width, height;
			int samplesPerPixel;


			static ptr cameraFromJSON(const nlohmann::json& in)
			{
				//TODO: in the future, we shall create different cameras
				//(ortographics, projective) depending on the parameters.
				ptr out(new Camera);

				out->pos = JSONHelper::vec4FromJSON(in["pos"]);
				out->up = JSONHelper::vec3FromJSON( in["up"] );
				out->look = JSONHelper::vec3FromJSON( in["look"] );

				out->width = in["width"].get<int>();
				out->height = in["height"].get<int>();
				out->samplesPerPixel = in["samplesPerPixel"].get<int>();
				out->FOV = in["FOV"].get<double>();
				out->aspectRatio = in["aspectRatio"].get<double>();

				return out;
			}
		};
	}
}

#endif