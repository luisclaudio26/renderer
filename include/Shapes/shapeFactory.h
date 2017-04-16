#ifndef _SHAPE_FACTORY_H_
#define _SHAPE_FACTORY_H_

#include <memory>
#include "../error.h"
#include "../BxDF/bxdfFactory.h"
#include "shape.h"
#include "./Shapes/sphere.h"
#include "./Shapes/plane.h"

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

				//TODO: THROW ERROR
				LogError("Unsupported shape.");
			}
		};
	}
}

#endif