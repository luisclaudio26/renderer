#include "../../include/BxDF/bxdf.h"
#include <cmath>
#include <iostream>

namespace Renderer
{
	namespace BxDF
	{
		#define OVER_PI 0.318309886
		#define PI 3.141592654

		void Lambertian::f(const glm::vec3& wi, const glm::vec3& wo, 
							const glm::vec3& normal, RGBSpectrum& out) const
		{
			out.r = color[0];
			out.g = color[1];
			out.b = color[2];

			out = out * OVER_PI;
		}

		float Lambertian::pdf(const glm::vec3& wi, const glm::vec3& wo, 
								const glm::vec3& normal) const
		{
			float d = glm::dot(wo, normal);
			if( d > 0 ) return d * OVER_PI;
			else return 0.0f;
		}

		void Lambertian::sampleBRDF(const glm::vec3& wi, const glm::vec3& normal, 
									glm::vec3& wo, float& p) const
		{
			//FROM LUAN FUJUN'S CODE!!!
			//This is samples a vector on a hemisphere,
			//weighted by the cosine with the normal
			//TODO: put this in local reference frame!!
			float x = ((float)rand()/RAND_MAX), y = ((float)rand()/RAND_MAX);
			const float term1 = 2.0f * PI * x;
			const float term2 = std::sqrt(1.0f - y);

			wo = glm::vec3(sin(term1) * term2, sqrt(y), cos(term1) * term2);
			p = this->pdf(wi, wo, normal);
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

		float Specular::pdf(const glm::vec3& wi, const glm::vec3& wo, 
								const glm::vec3& normal) const
		{
			return 0.0f;
		}

		void Specular::sampleBRDF(const glm::vec3& wi, const glm::vec3& normal, 
									glm::vec3& wo, float& p) const
		{
			return;
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