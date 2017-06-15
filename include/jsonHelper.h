#ifndef _JSON_HELPER_
#define _JSON_HELPER_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "../3rdparty/json.hpp"

namespace Renderer
{
	namespace JSONHelper
	{
		glm::vec4 vec4FromJSON(const nlohmann::json& in);
		glm::vec3 vec3FromJSON(const nlohmann::json& in);
		glm::vec2 vec2FromJSON(const nlohmann::json& in);
		glm::mat4 parseTransformations(const nlohmann::json& in);
	}
}

#endif