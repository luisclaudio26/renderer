#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <memory>
#include <string>
#include <vector>
#include "../geometry.h"
#include "../intersection.h"

namespace Renderer
{
	namespace Shapes
	{
		//forward declaration, avoiding file inclusion
		class Primitive;

		class Shape
		{
		public:
			typedef std::shared_ptr<Shape> ptr;

			BRDF::ptr material;

			virtual void intersect(const Geometry::Ray& r, Intersection& out) = 0;
			virtual void getPrimitives(std::vector<Primitive*>& out) = 0;

			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			virtual std::string str() = 0;
		};
	}
}

#endif