#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../geometry.h"
#include "shape.h"
#include "../Primitives/primSphere.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Shapes
	{
		class Sphere : public Shape
		{
		public:
			PrimSphere s;

			void intersect(const Geometry::Ray& r, Intersection& out) override;
			void getPrimitives(std::vector<Primitive*>& out) override;
			
			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			std::string str() override;
		};
	}
}

#endif