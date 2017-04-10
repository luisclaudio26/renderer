#include "../../include/Lights/pointLight.h"

namespace Renderer
{
	namespace Lighting
	{
		std::string PointLight::str()
		{
			return "[PointLight]";
		}

		void PointLight::prepare_sampling( const glm::vec3& pos, int n_samples )
		{

		}

		bool PointLight::has_next()
		{
			return false;
		}

		void PointLight::next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi)
		{

		}
	}
}