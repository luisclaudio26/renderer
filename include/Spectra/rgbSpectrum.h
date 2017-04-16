#ifndef SPECTRUM_H
#define SPECTRUM_H

namespace Renderer
{
	namespace Spectra
	{
		class RGBSpectrum
		{
		public:
			RGBSpectrum() : r(0.0f), g(0.0f), b(0.0f) {}
			RGBSpectrum(float r, float g, float b) : r(r), g(g), b(b) {}

			float r, g, b;

			RGBSpectrum operator*(float f);
			
			static RGBSpectrum black() { return RGBSpectrum(); }
		};
	}
}

#endif