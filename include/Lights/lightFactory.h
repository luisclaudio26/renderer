#ifndef _LIGHT_FACTORY_H_
#define _LIGHT_FACTORY_H_

#include "../../3rdparty/json.hpp"
#include "light.h"
#include "../error.h"
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
				else
					//TODO: THROW ERROR
					LogError("Unsupported light");
			}
		};
	}
}

#endif