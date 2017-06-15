#ifndef _PLANE_LIGHT_H_
#define _PLANE_LIGHT_H_

#include "../include/Lights/areaLight.h"
#include "../include/Primitives/triangle.h"

namespace Renderer
{
	namespace Lighting
	{
		using Shapes::Triangle;

		class PlaneLight : public AreaLight
		{
		public:
			glm::mat4 model2world;
			glm::mat3 bl, ur;

			void generateSamples();
		};
	}
}

#endif