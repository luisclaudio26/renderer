#ifndef BxDF_H
#define BxDF_H

#include <memory>
#include <glm/glm.hpp>
#include "../Spectra/rgbSpectrum.h"

namespace Renderer
{
	using namespace Spectra;
	
	namespace BxDF
	{
		class BRDF
		{
		public:
			typedef std::shared_ptr<BRDF> ptr;

			virtual void f(const glm::vec3& wi, const glm::vec3& wo, RGBSpectrum& out) const = 0;
		};

		class Lambertian : public BRDF
		{
		public:
			glm::vec3 color;
			void f(const glm::vec3& wi, const glm::vec3& wo, RGBSpectrum& out) const override;
		};
	}
}

#endif