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

				if(type.compare("lambertian") == 0)
				{
					Lambertian* lamb = new Lambertian;
					//For now, we're ignoring the spectrum type

					nlohmann::json param = in["param"];
					float r = param["color"][0]; 
					float g = param["color"][1]; 
					float b = param["color"][2];
					
					lamb->color = glm::vec3(r, g, b);

					return BRDF::ptr(lamb);
				}

				//TODO: THROW ERROR
				LogError("Unsupported material.");
			}
		};
	}
}

#endif