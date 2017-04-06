#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <glm/glm.hpp>
#include <string>
#include "BxDF/bxdf.h"

namespace Renderer
{
	using namespace BxDF;
	
	//TODO: Maybe this is not really
	//"geometric" stuff and should be
	//moved to another place.
	typedef struct _inter
	{
		bool valid;
		float t;
		glm::vec3 normal;

		BRDF::ptr material;

		void operator=(const _inter& lhs);
		std::string str();
	} Intersection;
}

#endif