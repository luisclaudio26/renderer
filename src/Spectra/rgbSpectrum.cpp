#include "../../include/Spectra/rgbSpectrum.h"
#include <cmath>

namespace Renderer
{
	namespace Spectra
	{
		RGBSpectrum RGBSpectrum::operator*(float f)
		{
			return RGBSpectrum(f*r, f*g, f*b);
		}

		RGBSpectrum RGBSpectrum::operator+(const RGBSpectrum& s)
		{
			return RGBSpectrum(r + s.r, g + s.g, b + s.b);
		}

		RGBSpectrum RGBSpectrum::operator=(const RGBSpectrum& s)
		{
			r = s.r; g = s.g; b = s.b;
			return *this;
		}

		RGBSpectrum RGBSpectrum::operator*(const RGBSpectrum& s)
		{
			return RGBSpectrum(r * s.r, g * s.g, b * s.b);
		}

		void RGBSpectrum::gammaEncode()
		{
			float inv22 = 1.0 / 2.2;
			r = pow(r, inv22);
			g = pow(g, inv22);
			b = pow(b, inv22);
		}
	}
}