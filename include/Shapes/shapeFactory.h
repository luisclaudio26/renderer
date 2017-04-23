#ifndef _SHAPE_FACTORY_H_
#define _SHAPE_FACTORY_H_

#include <memory>
#include <iostream>

#include "../../3rdparty/tiny_obj_loader.h"
#include "../error.h"
#include "../BxDF/bxdfFactory.h"
#include "shape.h"
#include "./Shapes/sphere.h"
#include "./Shapes/plane.h"
#include "./Shapes/meshobj.h"

namespace Renderer
{
	namespace Shapes
	{
		class ShapeFactory
		{
		public:

			static Shape::ptr create(const nlohmann::json& in)
			{
				std::string type = in["shape"].get<std::string>();
				BRDF::ptr mat = BxDFFactory::create( in["material"] );

				if(type.compare("sphere") == 0)
				{
					Sphere* s = new Sphere;
					s->radius = in["shapeParam"]["radius"].get<double>();
					s->center = JSONHelper::vec4FromJSON( in["pos"] );

					s->material = mat;

					return Shape::ptr(s);
				}
				else if(type.compare("plane") == 0)
				{
					Plane* p = new Plane;
					p->center = JSONHelper::vec4FromJSON( in["pos"] );
					p->normal = JSONHelper::vec3FromJSON( in["shapeParam"]["normal"] );

					p->material = mat;

					return Shape::ptr(p);
				}
				else if(type.compare("meshOBJ") == 0)
				{
					MeshOBJ* m = new MeshOBJ;

					std::string err;
					std::string path = in["shapeParam"]["path"].get<std::string>();
					tinyobj::LoadObj(&m->attrib, &m->shapes, &m->materials, &err, path.c_str());

					if(!err.empty())
					{
						std::string e("Error while loading mesh: ");
						LogError(e + err);
					}

					return Shape::ptr(m);
				}

				//TODO: THROW ERROR
				LogError("Unsupported shape.");
			}
		};
	}
}

#endif