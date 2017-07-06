#include "../../include/Integrator/pathtracer.h"
#include <omp.h>

#define N_SAMPLES 50

//TODO: THERE'S SOME PROBLEM WITH THE NORMALS OF THE PLANES,
//BECAUSE HALF OF THE PLANES ARE DARKER

namespace Renderer
{
	namespace Integration
	{
		using namespace Geometry;

		#define OVER_PI 0.318309886
		#define PI_OVER_2 1.570796327
		#define PI_TIMES_2 6.283185307
		#define PI 3.141592654

		glm::vec3 sample_hemisphere(const glm::vec3& normal)
		{
			float u, v, w;
			u = ((float)rand()/RAND_MAX) * 2.0f - 1.0f;
			v = ((float)rand()/RAND_MAX) * 2.0f - 1.0f;
			w = ((float)rand()/RAND_MAX) * 2.0f - 1.0f;

			glm::vec3 d(u, v, w);

			if( glm::dot(d, normal) < 0 )
				d = -d;

			return glm::normalize(d);
		}

		RGBSpectrum PathTracer::path_from(const Ray& start_ray, int depth) const
		{
			RGBSpectrum out(.0f, .0f, .0f), beta(1.0f, 1.0f, 1.0f);
			Ray ray = start_ray;

			int max = 1 + rand() % depth; //std::cout<<max<<", ";
			for(int bounce = 0; bounce < max; ++bounce)
			{
				//Compute intersection of this ray
				Intersection isect; scene->shootCameraRay(ray, isect);
				if(!isect.valid) break;

				//TODO: Emission light if bounce == 0
				//if(bounce == 0) out = out + isect.material->emission;

				//Compute direct lighting for this bounce,
				//and accumulate its contribution. This effectively
				//computes the contribution of a path with length BOUNCE
				//TODO: Do this for EVERY light source on the scene

				if(bounce == max-1)
				{
					Light::ptr L_ = scene->lights[0];
					L_->prepare_sampling( *scene, ray(isect.t) + 0.001f * isect.normal, 1 );
					
					RGBSpectrum L; glm::vec3 wi;
					L_->next_sample(L, wi);

					RGBSpectrum brdf; isect.material->f(wi, -ray.d, isect.normal, brdf);
					float cosWiN = glm::max(glm::dot(-wi, isect.normal), 0.0f);

					RGBSpectrum pBounce = L * brdf * cosWiN;
					out = (beta * pBounce);
				}
				else
				{
					//Update ray, so it shoots from the intersection
					//to a random direction.
					//TODO: Shoot ray based on BSDF sampling (importance sampling!)
					glm::vec3 old_d = ray.d;
					ray.o = ray(isect.t);
					ray.d = sample_hemisphere(isect.normal);

					//Update beta
					RGBSpectrum f;
					isect.material->f(ray.d, old_d, isect.normal, f);
					float cosWoN = glm::max(glm::dot(ray.d, isect.normal), 0.0f);

					beta = beta * (f * cosWoN);
				}

			}

			return out;
		}

		void PathTracer::integrate(const Ray& eye2obj, const Intersection& inter, RGBSpectrum& out) const
		{
			RGBSpectrum acc(0.0f, 0.0f, 0.0f);

			for(int i = 0; i < N_SAMPLES; ++i)
				acc = acc + path_from(eye2obj, 3);

			out = acc * (1.0f / N_SAMPLES);
		}
	}
}