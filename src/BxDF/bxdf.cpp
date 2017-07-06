#include "../../include/BxDF/bxdf.h"
#include <cmath>
#include <iostream>

namespace Renderer
{
	namespace BxDF
	{
		void Lambertian::f(const glm::vec3& wi, const glm::vec3& wo, const glm::vec3& normal, RGBSpectrum& out) const
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

		void Specular::f(const glm::vec3& wi, const glm::vec3& wo, const glm::vec3& normal, RGBSpectrum& out) const
		{
			glm::vec3 r = glm::reflect(wi, normal);
			float v = glm::max(glm::dot(r, wo), 0.0f);
			float spec = pow(v, this->gamma);

			out.r = color[0] + (1-color[0])*spec;
			out.g = color[1] + (1-color[1])*spec;
			out.b = color[2] + (1-color[2])*spec;
		}

		std::string Specular::str() const
		{
			std::string out("Specular[");
			
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