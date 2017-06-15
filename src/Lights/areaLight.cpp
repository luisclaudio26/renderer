#include "../../include/Lights/areaLight.h"

namespace Renderer
{
	namespace Lighting
	{		
		void AreaLight::prepare_sampling( const Scene::SceneManager& scene_handler, const glm::vec3& p, int n_samples )
		{
			return;
		}

		bool AreaLight::has_next()
		{
			return false;
		}

		void AreaLight::next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi )
		{
			return;
		}

		std::string AreaLight::str()
		{
			return std::string("[Area Light]");
		}
	}
}