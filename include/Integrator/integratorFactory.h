#ifndef _INTEGRATOR_FACTORY_H_
#define _INTEGRATOR_FACTORY_H_

#include "../../3rdparty/json.hpp"
#include "integrator.h"
#include "directLighting.h"

class IntegratorFactory
{
public:

	static Integrator::ptr create(const nlohmann::json& in)
	{
		std::string type = in["type"].get<std::string>();

		if(type.compare("DirectLighting") == 0)
			return Integrator::ptr(new DirectLighting);

		//TODO: THROW ERROR
		return Integrator::ptr(new DirectLighting);
	}
};

#endif