#ifndef _LIGHT_FACTORY_H_
#define _LIGHT_FACTORY_H_

#include "../../3rdparty/json.hpp"
#include "light.h"
#include "../error.h"
#include "pointLight.h"
#include "planeLight.h"

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
				std::string spectrumType = in["spectrumType"].get<std::string>();

				Spectra::RGBSpectrum spectrum;
				if(spectrumType.compare("RGB") == 0)
				{
					nlohmann::json jspec = in["spectrum"];
					spectrum = Spectra::RGBSpectrum(jspec[0].get<float>(),
													jspec[1].get<float>(),
													jspec[2].get<float>());
				}

				if(type.compare("point") == 0)
				{
					PointLight* pl = new PointLight;
					pl->pos = JSONHelper::vec3FromJSON( in["lightParam"]["pos"] );
					pl->falloff_a = in["lightParam"]["falloff_a"];
					pl->falloff_b = in["lightParam"]["falloff_b"];
					pl->light_spectrum = spectrum;

					return Light::ptr(pl);
				}
				else if(type.compare("area") == 0)
				{
					std::string shape = in["lightParam"]["shape"].get<std::string>();

					if( shape.compare("plane") == 0)
					{
						PlaneLight* pl = new PlaneLight;

						pl->model2world = JSONHelper::parseTransformations( in["lightParam"]["transformation"] );
						
						glm::vec2 bl, ur;
						bl = JSONHelper::vec2FromJSON( in["lightParam"]["shapeParam"]["bottomLeft"] );
						ur = JSONHelper::vec2FromJSON( in["lightParam"]["shapeParam"]["upperRight"] );

						glm::vec3 v0, v1, v2, v3;
						v0 = glm::vec3(0.0f, bl[0], bl[1]);
						v1 = glm::vec3(0.0f, ur[0], bl[1]);
						v2 = glm::vec3(0.0f, ur[0], ur[1]);
						v3 = glm::vec3(0.0f, bl[0], ur[1]);

						pl->bl.vertex[0] = v0; pl->bl.vertex[1] = v1; pl->bl.vertex[2] = v3;					
						pl->ur.vertex[0] = v1; pl->ur.vertex[1] = v2; pl->ur.vertex[2] = v3;		
						
						return Light::ptr(pl);
					}
					else
						LogError("Unsupported shape for area light");
				}
				else
					LogError("Unsupported light");
			}
		};
	}
}

#endif