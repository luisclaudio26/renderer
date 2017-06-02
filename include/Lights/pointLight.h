#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "light.h"
#include "../geometry.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Lighting
	{
		using Geometry::Ray;

		class PointLight : public Light
		{
		private:
			//all samples have, of course, the same direction
			//(as they from the light all to the same point).
			//This means that even if one, for some reason, takes
			//N samples of it, all the N samples will be identical.
			//For this, we precompute everything in prepare_sampling().
			bool occluded;
			int n_remaining_samples;
			Ray wi;
			Spectra::RGBSpectrum out;

		public:
			glm::vec3 pos;
			float falloff_a, falloff_b;
			
			//----------------------------
			//------ Light sampling ------
			//----------------------------
			void prepare_sampling( const Scene::SceneManager& scene_handler, const glm::vec3& p, int n_samples ) override;
			bool has_next() override;
			void next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi ) override;

			//---------------------------
			//----- Debugging tools -----
			//---------------------------
			std::string str() override;
		};
	}
}

#endif