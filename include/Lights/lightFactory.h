#ifndef _LIGHT_FACTORY_H_
#define _LIGHT_FACTORY_H_

#include "../../3rdparty/json.hpp"
#include "light.h"
#include "pointLight.h"

namespace Renderer
{
	namespace Lighting
	{
		class LightFactory
		{
		public:

			static Light::ptr create(const nlohmann::json& in)
			{
				std::string type = in["type"].get<std::string>();

				if(type.compare("point") == 0)
				{
					PointLight* pl = new PointLight;
					pl->pos = JSONHelper::vec4FromJSON( in["lightParam"]["pos"] );

					return Light::ptr(pl);
				}

				//TODO: THROW ERROR
				return Light::ptr(new PointLight);
			}
		};
	}
}

#endif