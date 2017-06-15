#include "../../include/Spectra/rgbSpectrum.h"

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
	}
}