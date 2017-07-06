#include "../../include/Lights/areaLight.h"
#include "../../include/geometry.h"
#include "../../include/intersection.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace Renderer
{
	namespace Lighting
	{		
		using Geometry::Ray;

		void AreaLight::prepare_sampling( const Scene::SceneManager& scene_handler, const glm::vec3& p, int n_samples )
		{
			this->scene = &scene_handler;
			this->origin = p;
			this->n_remaining_samples = n_samples;

			generateSamples();
		}

		bool AreaLight::has_next()
		{
			return n_remaining_samples > 0;
		}

		void AreaLight::next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi )
		{
			glm::vec3 sample = samples[ n_remaining_samples ];			

			Ray ray;
			ray.o = origin;
			ray.d = glm::normalize(sample-origin);

			wi = -ray.d; n_remaining_samples--;

			Intersection I; scene->shootCameraRay( ray, I );
			out = (I.valid && 0.0f <= I.t && I.t <= 1.0f) ? RGBSpectrum::black() : light_spectrum;
		}

		std::string AreaLight::str()
		{
			return std::string("[Area Light]");
		}
	}
}