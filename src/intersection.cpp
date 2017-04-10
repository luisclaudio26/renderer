#include "../include/intersection.h"
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	std::string Intersection::str()
	{
		std::string s("[Intersection: ");
		s += this->valid ? "Valid, " : "No Intersection, ";
		s += std::to_string(this->t);
		s += ", ";
		s += glm::to_string(this->normal);
		s += "]";
		return s;
	}

	void Intersection::operator=(const Intersection& lhs)
	{
		t = lhs.t;
		valid = lhs.valid;
		normal = lhs.normal;
		material = lhs.material;
	}
}