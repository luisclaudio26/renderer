#ifndef _POINT_LIGHT_H_
#define _POINT_LIGHT_H_

#include "light.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Lighting
	{
		class PointLight : public Light
		{
		public:
			glm::vec4 pos;

			//----------------------------
			//------ Light sampling ------
			//----------------------------
			void prepare_sampling( const glm::vec3& pos, int n_samples ) override;
			bool has_next() override;
			void next_sample( Spectra::RGBSpectrum& out, glm::vec3& wi) override;

			//---------------------------
			//----- Debugging tools -----
			//---------------------------
			std::string str() override;
		};
	}
}

#endif