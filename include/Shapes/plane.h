#ifndef _PLANE_H_
#define _PLANE_H_

#include "shape.h"
#include "../geometry.h"
#include "../Primitives/triangle.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Shapes
	{
		class Plane : public Shape
		{
		private:
			bool transformed;

		public:
			//Bottom-Left, Upper-Right triangles
			Triangle bl, ur;

			Plane():transformed(false) {}
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