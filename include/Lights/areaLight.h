#ifndef _AREA_LIGHT_H_
#define _AREA_LIGHT_H_

#include "light.h"
#include "../geometry.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Lighting
	{
		class AreaLight : public Light
		{
		public:
			void prepare_sampling( const Scene::SceneManager& scene_handler, const glm::vec3& p, int n_samples ) override;
			bool has_next() override;
			void next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi ) override;

			std::string str() override;
		};
	}
}

#endif