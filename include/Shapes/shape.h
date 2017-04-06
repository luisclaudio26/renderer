#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <memory>
#include <string>
#include "../geometry.h"
#include "../intersection.h"

namespace Renderer
{
	namespace Shapes
	{
		class Shape
		{
		public:
			typedef std::shared_ptr<Shape> ptr;

			BRDF::ptr material;

			virtual void intersect(const Geometry::Ray& r, Intersection& out) = 0;

			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			virtual std::string str() = 0;
		};
	}
}

#endif