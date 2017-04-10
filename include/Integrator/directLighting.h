#ifndef _DIRECT_LIGHTING_H_
#define _DIRECT_LIGHTING_H_

#include "integrator.h"

namespace Renderer
{
	namespace Integration
	{
		using namespace Geometry;

		class DirectLighting : public Integrator
		{
		protected:
			virtual void integrate(const Ray& eye2obj, 
									const Intersection& inter, RGBSpectrum& out) const override;
		};
	}
}

#endif