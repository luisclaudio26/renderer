#ifndef _INTEGRATOR_FACTORY_H_
#define _INTEGRATOR_FACTORY_H_

#include "../../3rdparty/json.hpp"
#include "../error.h"
#include "integrator.h"
#include "directLighting.h"

namespace Renderer
{
	namespace Integration
	{
		class IntegratorFactory
		{
		public:

			static Integrator::ptr create(const nlohmann::json& in)
			{
				std::string type = in["type"].get<std::string>();

				if(type.compare("DirectLighting") == 0)
					return Integrator::ptr(new DirectLighting);

				//if we're here, there was some error
				LogError("Unsupported integrator.");

			}
		};
	}
}

#endif