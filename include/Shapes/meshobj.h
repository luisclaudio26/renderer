#ifndef _MESHOBJ_H_
#define _MESHOBJ_H_

#include "../geometry.h"
#include "shape.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../../3rdparty/tiny_obj_loader.h"

namespace Renderer
{
	namespace Shapes
	{
		class MeshOBJ : public Shape
		{
		public:
			tinyobj::attrib_t attrib;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			void intersect(const Geometry::Ray& r, Intersection& out) override;

			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			std::string str() override;
		};
	}
}

#endif