#include "../../include/Integrator/pathtracer.h"

#define N_SAMPLES 32

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
			out.r = inter.material->emission[0];
			out.g = inter.material->emission[1];
			out.b = inter.material->emission[2];

			return out;
		}

		void PathTracer::integrate(const Ray& eye2obj, const Intersection& inter, RGBSpectrum& out) const
		{
			if(inter.valid)
			{
				RGBSpectrum indirect(0.0f, 0.0f, 0.0f);

				for(int i = 0; i < N_SAMPLES; i++)
				{
					Ray newR; 
					newR.o = eye2obj(inter.t); 
					newR.d = sample_hemisphere(inter.normal);

					RGBSpectrum sample = tracepath( newR, 1 );

					indirect = indirect + sample;
				}

				out.r = inter.material->emission[0] + indirect.r / N_SAMPLES;
				out.g = inter.material->emission[1] + indirect.g / N_SAMPLES;
				out.b = inter.material->emission[2] + indirect.b / N_SAMPLES;
			}
			else 
				out = RGBSpectrum::black();
		}
	}
}