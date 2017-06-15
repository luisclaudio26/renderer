#include "../../include/Integrator/pathtracer.h"

#define N_SAMPLES 100

namespace Renderer
{
	namespace Integration
	{
		using namespace Geometry;

		#define PI_OVER_2 1.570796327
		#define PI_TIMES_2 6.283185307
		#define PI 3.141592654

		glm::vec3 sample_hemisphere(const glm::vec3& normal)
		{
			/*
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
			out[2] = cos(e); */


			float u = (float)rand()/RAND_MAX;
			float v = (float)rand()/RAND_MAX;

			const float r = sqrt(u);
			const float theta = PI_TIMES_2 * v;

			const float x = r * cos(theta);
			const float y = r * sin(theta);

			return glm::vec3(x, y, sqrt(glm::max(0.0f, 1.0f - u)));
		}

		RGBSpectrum PathTracer::tracepath(const Ray& r, int depth) const
		{
			RGBSpectrum out = RGBSpectrum::black();

			//max depth reached
			if(depth == 0) return out;
			
			//find intersection
			Intersection inter; scene->shootCameraRay( r, inter );
			if(!inter.valid) return out;

			//we found an intersection. Just return
			//without recursing (first verstion)
			return inter.material->emission;
		}

		void PathTracer::integrate(const Ray& eye2obj, const Intersection& inter, RGBSpectrum& out) const
		{
			if(inter.valid)
			{
				glm::vec3 wo = -eye2obj.d;
				RGBSpectrum indirect(0.0f, 0.0f, 0.0f);

				for(int i = 0; i < N_SAMPLES; i++)
				{
					//get a new direction to shoot ray
					Ray newR; 
					newR.o = eye2obj(inter.t); 
					newR.d = sample_hemisphere(inter.normal);

					//trace path in this direction
					RGBSpectrum Li = tracepath( newR, 1 );

					glm::vec3 wi = -newR.d;
					RGBSpectrum brdf; inter.material->f(wi, wo, inter.normal, brdf);

					//float cosWiN = glm::max(glm::dot(-wi, inter.normal), 0.0f);

					indirect = indirect + (Li * brdf);
				}

				out = inter.material->emission + indirect * (1.0f/N_SAMPLES);
			}
			else 
				out = RGBSpectrum::black();
		}
	}
}