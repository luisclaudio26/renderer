#ifndef _AREA_LIGHT_H_
#define _AREA_LIGHT_H_

#include "light.h"
#include "../geometry.h"
#include "../scene.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>

namespace Renderer
{
	namespace Lighting
	{
		class AreaLight : public Light
		{
		protected:
			int n_remaining_samples;

			const Scene::SceneManager *scene;

			//point where the rays are being shoot from
			glm::vec3 origin;

			//samples are 3D because they're actual
			//points in world coordinate space
			std::vector<glm::vec3> samples;

			//each specific area light knows how to generate
			//its samples in world coordinates
			virtual void generateSamples() = 0;

		public:
			void prepare_sampling( const Scene::SceneManager& scene_handler, const glm::vec3& p, int n_samples ) override;
			bool has_next() override;
			void next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi ) override;

			std::string str() override;
		};
	}
}

#endif