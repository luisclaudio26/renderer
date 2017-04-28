#ifndef _MESHOBJ_H_
#define _MESHOBJ_H_

#include "shape.h"
#include "../geometry.h"
#include "../../3rdparty/tiny_obj_loader.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Shapes
	{
		typedef struct 
		{
			glm::vec3 vertex[3];
		} TriFace;

		typedef struct
		{
			std::vector<TriFace> faces;
		} ShapeOBJ;

		class MeshOBJ : public Shape
		{
		public:
			std::vector<ShapeOBJ> shapes;

			MeshOBJ(const std::vector<tinyobj::shape_t>& shapes, const tinyobj::attrib_t& attrib);

			void intersect(const Geometry::Ray& r, Intersection& out) override;

			//-----------------------------
			//------ Debugging tools ------
			//-----------------------------
			std::string str() override;
		};
	}
}

#endif