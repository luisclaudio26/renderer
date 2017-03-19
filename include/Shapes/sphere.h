#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "shape.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Shapes
	{
		class Sphere : public Shape
		{
		public:
			double radius;
			glm::vec4 center;

			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			std::string str() override;
		};
	}
}

#endif