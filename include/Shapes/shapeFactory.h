#ifndef _SHAPE_FACTORY_H_
#define _SHAPE_FACTORY_H_

#include <memory>
#include <iostream>
#include <glm/gtx/transform.hpp>

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

			static glm::mat4 parseTransformations(const nlohmann::json& in)
			{
				glm::mat4 out(1.0f);
				glm::mat4 scl(1.0f), rot(1.0f), trans(1.0f);

				if( in.find("scale") != in.end() )
				{
					glm::vec3 scl_v = JSONHelper::vec3FromJSON( in["scale"] );
					scl = glm::scale(scl_v);
				}

				if( in.find("rotate") != in.end() )
				{
					glm::vec4 rot_v = JSONHelper::vec4FromJSON( in["rotate"] );
					rot = glm::rotate(rot_v[3], glm::vec3(rot_v));
				}

				if( in.find("translate") != in.end() )
				{
					glm::vec3 trans_v = JSONHelper::vec3FromJSON( in["translate"] );
					trans = glm::translate(trans_v);
				}

				std::string order = in["order"].get<std::string>();
				for(auto t = order.begin(); t != order.end(); ++t)
				{
					if(*t == 't' || *t == 'T')
						out = trans * out;
					if(*t == 'r' || *t == 'R')
						out = rot * out;
					if(*t == 's' || *t == 'S')
						out = scl * out;
				}

				return out;
			}

			static Shape::ptr create(const nlohmann::json& in)
			{
				std::string type = in["shape"].get<std::string>();
				BRDF::ptr mat = BxDFFactory::create( in["material"] );
				glm::mat4 model2world = ShapeFactory::parseTransformations( in["transformation"] );

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
					v0 = glm::vec3(0.0f, bl[0], bl[1]);
					v1 = glm::vec3(0.0f, ur[0], bl[1]);
					v2 = glm::vec3(0.0f, ur[0], ur[1]);
					v3 = glm::vec3(0.0f, bl[0], ur[1]);

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