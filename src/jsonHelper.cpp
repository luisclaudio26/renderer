#include "../include/jsonHelper.h"

namespace Renderer
{
	namespace JSONHelper
	{
		glm::vec4 vec4FromJSON(const nlohmann::json& in)
		{
			glm::vec4 out;
			out.x = in[0].get<double>();
			out.y = in[1].get<double>();
			out.z = in[2].get<double>();
			out.w = in[3].get<double>();
			return out;
		}

		glm::vec3 vec3FromJSON(const nlohmann::json& in)
		{
			glm::vec3 out;
			out.x = in[0].get<double>();
			out.y = in[1].get<double>();
			out.z = in[2].get<double>();
			return out;
		}

		glm::vec2 vec2FromJSON(const nlohmann::json& in)
		{
			glm::vec2 out;
			out.x = in[0].get<double>();
			out.y = in[1].get<double>();
			return out;
		}
	}
}
