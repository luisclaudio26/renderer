#include "../../include/Lights/planeLight.h"
#include <cstdlib>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace Renderer
{
	namespace Lighting
	{
		void PlaneLight::generateSamples()
		{
			bool upper = (rand() % 2);

			samples.clear();

			for(int i = 0; i < n_remaining_samples; ++i)
			{
				float x, y, z;
				x = 0.5f * (float)rand() / RAND_MAX;
				y = 0.5f * (float)rand() / RAND_MAX;
				z = 1 - x - y;

				//point in barycentric coordinates
				glm::vec3 p = glm::vec3(x, y, z);
				glm::vec3 s;

				s = upper ? ur * p : bl * p;

				samples.push_back(s);
				upper = !upper;
			}
		}
	}
}