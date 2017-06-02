#ifndef _MESHOBJ_H_
#define _MESHOBJ_H_

#include "shape.h"
#include "../geometry.h"
#include "../Primitives/triangle.h"
#include "../../3rdparty/tiny_obj_loader.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Shapes
	{
		typedef struct
		{
			std::vector<Triangle> faces;
		} ShapeOBJ;

		class MeshOBJ : public Shape
		{
		private:
			bool transformed;
			
		public:
			std::vector<ShapeOBJ> shapes;

			void setGeometryData(const std::vector<tinyobj::shape_t>& shapes, const tinyobj::attrib_t& attrib,
									const BRDF::ptr material, const glm::mat4 model2world);
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