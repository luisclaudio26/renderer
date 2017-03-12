#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "../shape.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

class Sphere : public Shape
{
public:
	double radius;
	glm::vec4 center;

	std::string str() override
	{
		std::string s("");
		s += "[Radius: ";
		s += std::to_string(this->radius);
		s += ", Center: ";
		s += glm::to_string(this->center);
		s += "]";
		return s;
	}
};

#endif