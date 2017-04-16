#include "../../include/Spectra/rgbSpectrum.h"

namespace Renderer
{
	namespace Spectra
	{
		RGBSpectrum RGBSpectrum::operator*(float f)
		{
			return RGBSpectrum(f*r, f*g, f*b);
		}
	}
}