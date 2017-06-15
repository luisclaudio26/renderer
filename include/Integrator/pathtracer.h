#ifndef _PATH_TRACER_H_
#define _PATH_TRACER_H_

#include "integrator.h"

namespace Renderer
{
	namespace Integration
	{
		using namespace Geometry;

		class PathTracer : public Integrator
		{
		protected:
			void integrate(const Ray& eye2obj, 
							const Intersection& inter, RGBSpectrum& out) const override;
		public:
			RGBSpectrum tracepath(const Ray& r, int depth) const;
		};
	}
}

#endif