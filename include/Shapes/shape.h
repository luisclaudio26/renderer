#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <memory>
#include <string>

namespace Renderer
{
	namespace Shapes
	{
		class Shape
		{
		public:
			typedef std::shared_ptr<Shape> ptr;

			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			virtual std::string str() = 0;
		};
	}
}

#endif