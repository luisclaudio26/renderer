#include "../../include/Integrator/directLighting.h"

//Where should this be?
#define SAMPLES_PER_LIGHT 1

namespace Renderer
{
	namespace Integration
	{
		void DirectLighting::integrate(const Ray& eye2obj, const Intersection& inter, RGBSpectrum& out) const
		{
			out.r = out.g = out.b = 0.0f;
			BRDF::ptr material = inter.material;
			glm::vec3 wo = eye2obj.d;

			//TODO: How to better do this, without copying code
			//for each channel?
			//Sample all lights
			for(auto l : this->scene->lights)
			{
				//sample each light.
				//We extract only one sample for point/directional lights,
				//more for area lights, for example.
				l->prepare_sampling( eye2obj(inter.t), SAMPLES_PER_LIGHT );

				while( l->has_next() )
				{
					RGBSpectrum ls_spectrum; glm::vec3 wi;
					l->next_sample(ls_spectrum, wi);

					RGBSpectrum brdf;
					material->f(wi, wo, brdf);

					float cosWiN = glm::dot(wi, wo);

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