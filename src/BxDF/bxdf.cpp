#include "../../include/BxDF/bxdf.h"

namespace Renderer
{
	namespace BxDF
	{
		void Lambertian::f(const glm::vec3& wi, const glm::vec3& wo, RGBSpectrum& out) const
		{
			out.r = color[0];
			out.g = color[1];
			out.b = color[2];
		}
	}
}