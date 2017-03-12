#include "../../include/Shapes/sphere.h"

std::string Sphere::str()
{
	std::string s("");
	
	s += "[Radius: ";
	s += std::to_string(this->radius);
	s += ", Center: ";
	s += glm::to_string(this->center);
	s += "]";

	return s;
}