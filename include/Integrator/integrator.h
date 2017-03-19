#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include <memory>

namespace Renderer
{
	namespace Integration
	{
		class Integrator
		{
		public:
			typedef std::unique_ptr<Integrator> ptr;
		};
	}
}

#endif