#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <memory>
#include <string>
#include <glm/glm.hpp>
#include "../Spectra/rgbSpectrum.h"

namespace Renderer
{
	//Bizarre forward declaration
	namespace Scene { class SceneManager; }

	namespace Lighting
	{
		class Light
		{
		protected:

		public:
			typedef std::shared_ptr<Light> ptr;

			Spectra::RGBSpectrum light_spectrum;

			//----------------------------
			//------ Light sampling ------
			//----------------------------
			virtual void prepare_sampling( const Scene::SceneManager& scene_handler, const glm::vec3& pos, int n_samples ) = 0;
			virtual bool has_next() = 0;
			virtual void next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi ) = 0;

			//---------------------------
			//----- Debugging tools -----
			//---------------------------
			virtual std::string str() = 0;
		};
	}
}

#endif