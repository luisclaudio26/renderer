#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <memory>
#include <string>

namespace Renderer
{
	namespace Lighting
	{
		class Light
		{
		public:
			typedef std::shared_ptr<Light> ptr;

			//---------------------------
			//----- Debugging tools -----
			//---------------------------
			virtual std::string str() = 0;
		};
	}
}

#endif