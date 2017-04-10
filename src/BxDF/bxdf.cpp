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

		std::string Lambertian::str() const
		{
			std::string out("Lambertian[");
			
			out += std::to_string(color[0]);
			out += ", ";
			out += std::to_string(color[1]);
			out += ", ";
			out += std::to_string(color[2]);
			out += "]";

			return out;
		}
	}
}