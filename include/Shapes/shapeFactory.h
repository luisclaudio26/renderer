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
				glm::mat4 model2world = JSONHelper::parseTransformations( in["transformation"] );

				if(type.compare("sphere") == 0)
				{
					Sphere* s = new Sphere;
					s->s.radius = in["shapeParam"]["radius"].get<double>();
					s->s.center = JSONHelper::vec4FromJSON( in["pos"] );

					s->s.material = mat;
					s->model2world = model2world;

					return Shape::ptr(s);
				}
				else if(type.compare("plane") == 0)
				{
					Plane* p = new Plane;

					glm::vec2 bl = JSONHelper::vec2FromJSON( in["shapeParam"]["bottomLeft"] );
					glm::vec2 ur = JSONHelper::vec2FromJSON( in["shapeParam"]["upperRight"] );
					
					//TODO: Implement this correctly!
					//Triangle is sent to xz-plane, then we apply
					//the transformation we want.
					glm::vec3 v0, v1, v2, v3;
					v0 = glm::vec3(bl[0], 0.0f, bl[1]);
					v1 = glm::vec3(ur[0], 0.0f, bl[1]);
					v2 = glm::vec3(ur[0], 0.0f, ur[1]);
					v3 = glm::vec3(bl[0], 0.0f, ur[1]);

					p->bl.vertex[0] = v0; p->bl.vertex[1] = v1; p->bl.vertex[2] = v3;					
					p->ur.vertex[0] = v1; p->ur.vertex[1] = v2; p->ur.vertex[2] = v3;
					p->ur.material = mat;
					p->bl.material = mat;
					p->model2world = model2world;

					return Shape::ptr(p);
				}
				else if(type.compare("meshOBJ") == 0)
				{
					std::string path = in["shapeParam"]["path"].get<std::string>();

					std::vector<tinyobj::shape_t> shapes;
					std::vector<tinyobj::material_t> materials;
					std::string err; tinyobj::attrib_t attrib;
					
					tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str());

					if(!err.empty())
					{
						std::string e("Error while loading mesh: ");
						LogError(e + err);
					}

					MeshOBJ* m = new MeshOBJ;
					m->setGeometryData(shapes, attrib, mat, model2world);

					return Shape::ptr(m);
				}

				LogError("Unsupported shape.");
			}
		};
	}
}

#endif