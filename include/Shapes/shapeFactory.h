#ifndef _SHAPE_FACTORY_H_
#define _SHAPE_FACTORY_H_

#include <memory>
#include "shape.h"
#include "./Shapes/sphere.h"

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

			return std::unique_ptr<Shape>(s);
		}

		//TODO: THROW ERROR
		return std::unique_ptr<Shape>(new Sphere);
	}
};

#endif