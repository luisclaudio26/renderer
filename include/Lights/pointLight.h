#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "light.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Lighting
	{
		class PointLight : public Light
		{
		public:
			glm::vec4 pos;

			//---------------------------
			//----- Debugging tools -----
			//---------------------------
			std::string str() override;
		};
	}
}

#endif