#include "../../include/Integrator/directLighting.h"

#include <iostream>

//Where should this be?
#define SAMPLES_PER_LIGHT 1

namespace Renderer
{
	namespace Integration
	{
		void DirectLighting::integrate(const Ray& eye2obj, const Intersection& inter, RGBSpectrum& out) const
		{
			BRDF::ptr material = inter.material;

			//if intersection is not valid, then return background color
			//(which will be black by default).
			//It is not efficient to check if intersection is valid here
			//in integrate(), but in future integration methods, where we
			//will allow environment maps and stuff alike, it will be useful.
			if(!inter.valid)
			{
				out = RGBSpectrum::black();
				return;
			}

			out.r = out.g = out.b = 0.0f;
			glm::vec3 wo = -eye2obj.d; //we want wo to go from object to eye

			//TODO: How to better do this, without copying code
			//for each channel?
			//Sample all lights
			for(auto l : this->scene->lights)
			{
				//sample each light.
				//We extract only one sample for point/directional lights,
				//more for area lights, for example.
				l->prepare_sampling( *this->scene, eye2obj(inter.t), SAMPLES_PER_LIGHT );

				while( l->has_next() )
				{
					RGBSpectrum ls_spectrum; glm::vec3 wi;
					l->next_sample(ls_spectrum, wi);

					RGBSpectrum brdf;
					material->f(wi, wo, inter.normal, brdf);

					float cosWiN = glm::max(glm::dot(-wi, inter.normal), 0.0f);

					out.r += ls_spectrum.r * brdf.r * cosWiN;
					out.g += ls_spectrum.g * brdf.g * cosWiN;
					out.b += ls_spectrum.b * brdf.b * cosWiN;
				}
			}

			const int n = this->scene->lights.size();
			out.r /= n;
			out.g /= n;
			out.b /= n;

			return;
		}
	}
}