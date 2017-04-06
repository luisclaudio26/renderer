#ifndef _SHAPE_FACTORY_H_
#define _SHAPE_FACTORY_H_

#include <memory>
#include "../error.h"
#include "shape.h"
#include "./Shapes/sphere.h"
#include "../BxDF/bxdfFactory.h"

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

				if(type.compare("sphere") == 0)
				{
					Sphere* s = new Sphere;
					s->radius = in["shapeParam"]["radius"].get<double>();
					s->center = JSONHelper::vec4FromJSON( in["pos"] );

					s->material = BxDFFactory::create( in["material"] );

					return Shape::ptr(s);
				}

				//TODO: THROW ERROR
				LogError("Unsupported shape.");
			}
		};
	}
}

#endif