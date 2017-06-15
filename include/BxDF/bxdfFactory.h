#ifndef BXDF_FACTORY_H
#define BXDF_FACTORY_H

#include "../3rdparty/json.hpp"

namespace Renderer
{
	namespace BxDF
	{
		class BxDFFactory
		{
		public:

			static BRDF::ptr create(const nlohmann::json& in)
			{
				std::string type = in["type"].get<std::string>();

				float e_r = in["emission"][0];
				float e_g = in["emission"][1];
				float e_b = in["emission"][2];
				glm::vec3 emission(e_r, e_g, e_b);

				if(type.compare("lambertian") == 0)
				{
					Lambertian* lamb = new Lambertian;
					//For now, we're ignoring the spectrum type

					nlohmann::json param = in["param"];
					float r = param["color"][0]; 
					float g = param["color"][1]; 
					float b = param["color"][2];
					
					lamb->color = glm::vec3(r, g, b);
					lamb->emission = emission;

					return BRDF::ptr(lamb);
				}
				else if(type.compare("specular") == 0)
				{
					Specular *spec = new Specular;
					nlohmann::json param = in["param"];
					float r = param["color"][0]; 
					float g = param["color"][1]; 
					float b = param["color"][2];
					
					spec->color = glm::vec3(r, g, b);
					spec->gamma = param["gamma"].get<float>();
					spec->emission = emission;
					
					return BRDF::ptr(spec);
				}

				//TODO: THROW ERROR
				LogError("Unsupported material.");
			}
		};
	}
}

#endif