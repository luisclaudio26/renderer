#ifndef BxDF_H
#define BxDF_H

#include <memory>
#include <glm/glm.hpp>
#include <string>
#include "../Spectra/rgbSpectrum.h"

namespace Renderer
{
	using namespace Spectra;
	
	namespace BxDF
	{
		//Maybe it is more clever to transform Wo to a reference frame
		//where Normal is the Y-axis, Wi x Normal is X-axis and
		//Y x X is the Z-axis (where _ x _ is cross product). This would
		//simplify calculus and get us ridden of dealing with normal and
		//even Wi. But is this faster? Don't know
		class BRDF
		{
		public:
			glm::vec3 emission;

			typedef std::shared_ptr<BRDF> ptr;

			virtual void f(const glm::vec3& wi, const glm::vec3& wo, const glm::vec3& normal, RGBSpectrum& out) const = 0;
			virtual std::string str() const { return std::string("[Base BRDF]"); };
		};

		class Lambertian : public BRDF
		{
		public:
			glm::vec3 color;
			void f(const glm::vec3& wi, const glm::vec3& wo, const glm::vec3& normal, RGBSpectrum& out) const override;
			std::string str() const override;
		};

		class Specular : public BRDF
		{
		public:
			glm::vec3 color; float gamma;
			void f(const glm::vec3& wi, const glm::vec3& wo, const glm::vec3& normal, RGBSpectrum& out) const override;
			std::string str() const override;
		};
	}
}

#endif