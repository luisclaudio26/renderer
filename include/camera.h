#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "jsonHelper.h"

class Camera
{
public:

	glm::vec4 pos;
	glm::vec3 up, look;

	double aspectRatio, FOV;
	int width, height;
	int samplesPerPixel;


	static void cameraFromJSON(const nlohmann::json& in, Camera& out)
	{
		out.pos = JSONHelper::vec4FromJSON(in["pos"]);
		out.up = JSONHelper::vec3FromJSON( in["up"] );
		out.look = JSONHelper::vec3FromJSON( in["look"] );

		out.width = in["width"].get<int>();
		out.height = in["height"].get<int>();
		out.samplesPerPixel = in["samplesPerPixel"].get<int>();
		out.FOV = in["FOV"].get<double>();
		out.aspectRatio = in["aspectRatio"].get<double>();
	}
};

#endif