#include "../../include/Integrator/pathtracer.h"
#include <omp.h>

#define N_SAMPLES 5
#define P_TERMINATE 0.25

namespace Renderer
{
	namespace Integration
	{
		using namespace Geometry;

		#define OVER_PI 0.318309886
		#define PI_OVER_2 1.570796327
		#define PI_TIMES_2 6.283185307
		#define PI 3.141592654
		#define RAND01 ((float)rand()/RAND_MAX)

		glm::vec3 sample_hemisphere(const glm::vec3& normal)
		{
			float elevation = acos(normal[2]);
			float azymuth = atan2(normal[1], normal[0]);

			float d_e = (((float)rand()/RAND_MAX) * 2.0f - 1.0f) * PI_OVER_2;
			float d_a = ((float)rand()/RAND_MAX) * PI_TIMES_2;

			float e = elevation+d_e;
			float a = azymuth+d_a;

			//assert elevation is in [0,pi] 
			//and azymuth is in [0,2pi]
			if( e > PI ) {
				e = 2*PI - e;
				a = a - PI;
			}

			if( a > 2*PI ) a = a - 2*PI;

			glm::vec3 out;
			out[0] = sin(e) * cos(a);
			out[1] = sin(e) * sin(a);
			out[2] = cos(e);

			return out;
		}

		RGBSpectrum PathTracer::path_from(const Ray& start_ray) const
		{
			RGBSpectrum out(.0f, .0f, .0f), beta(1.0f, 1.0f, 1.0f);
			Ray ray = start_ray;

			for(int bounce = 0; ; ++bounce)
			{
				//Compute intersection of this ray
				Intersection isect; scene->shootCameraRay(ray, isect);
				if(!isect.valid) break;

				//TODO: Emission light if bounce == 0
				if(bounce == 0) out = out + isect.material->emission;

				//Compute direct lighting for this bounce,
				//and accumulate its contribution. This effectively
				//computes the contribution of a path with length BOUNCE
				//TODO: Do this for EVERY light source on the scene
				Light::ptr L_ = scene->lights[0];
				L_->prepare_sampling( *scene, ray(isect.t) + 0.001f * isect.normal, 1 );
				
				RGBSpectrum L; glm::vec3 wi;
				L_->next_sample(L, wi);

				RGBSpectrum brdf; isect.material->f(wi, -ray.d, isect.normal, brdf);
				float cosWiN = glm::max(glm::dot(-wi, isect.normal), 0.0f);

				RGBSpectrum pBounce = L * brdf * cosWiN;
				out = out + (beta * pBounce);

				//Update ray, so it shoots from the intersection
				//to a random direction.
				//TODO: Shoot ray based on BSDF sampling (importance sampling!)
				glm::vec3 old_d = ray.d; float pdf;
				ray.o = ray(isect.t) + 0.001f * isect.normal;
				//ray.d = sample_hemisphere(isect.normal);
				isect.material->sampleBRDF(-old_d, isect.normal, ray.d, pdf);

				//Update beta
				RGBSpectrum f;
				isect.material->f(ray.d, old_d, isect.normal, f);
				float cosWoN = glm::max(glm::dot(ray.d, isect.normal), 0.0f);

				beta = beta * (f * (cosWoN * 1.0/pdf));

				//russian roulette termination
				if( RAND01 < P_TERMINATE ) break;
				else beta = beta * (1/(1-P_TERMINATE));
			}

			return out;
		}

		void PathTracer::integrate(const Ray& eye2obj, const Intersection& inter, RGBSpectrum& out) const
		{
			RGBSpectrum acc(0.0f, 0.0f, 0.0f);

			for(int i = 0; i < N_SAMPLES; ++i)
				acc = acc + path_from(eye2obj);

			out = acc * (1.0f / N_SAMPLES);
		}
	}
}