#include "../../include/Lights/pointLight.h"
#include "../../include/scene.h"

namespace Renderer
{
	namespace Lighting
	{
		std::string PointLight::str()
		{
			return "[PointLight]";
		}

		void PointLight::prepare_sampling( const Scene::SceneManager& scene_handler, const glm::vec3& pos, int n_samples )
		{
			this->n_remaining_samples = n_samples;
			this->wi.o = glm::vec3(this->pos);
			this->wi.d = this->wi.o - pos;

			//Check for occlusion
			Intersection in; scene_handler.shootCameraRay(-wi, in);
			this->out = in.valid ? RGBSpectrum::black() : this->light_spectrum;
		}

		bool PointLight::has_next()
		{
			return this->n_remaining_samples > 0;
		}

		void PointLight::next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi )
		{
			out = this->out;
			wi = this->wi.d;
			this->n_remaining_samples--;
		}
	}
}