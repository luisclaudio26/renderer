#include "../../include/Shapes/sphere.h"
#include <cmath>

#include <iostream>

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		std::string Sphere::str()
		{
			std::string s("");
			
			s += "[Radius: ";
			s += std::to_string(this->s.radius);
			s += ", Center: ";
			s += glm::to_string(this->s.center);
			s += ", Material: ";
			s += this->material->str();
			s += "]";

			return s;
		}

		void Sphere::getPrimitives(std::vector<Primitive*>& out)
		{
			out.push_back(&this->s);
		}

		void Sphere::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;
			
			Intersection I; s.intersect(r, I);
			if(I.valid)
			{
				out = I;
				out.material = material;
			}
			
			/*
			//I don't know where to move this.
			const float EPS = 0.0001;

			glm::vec3 center = glm::vec3(this->center);

			float a = glm::dot(r.d, r.d);
			float b = 2.0f * glm::dot( r.d, r.o - center );
			float c = glm::dot(center, center) - 2.0f * glm::dot(center, r.o) + glm::dot(r.o, r.o) - radius*radius;

			//Neither this
			if( fabs(a) < EPS ) 
			{
				out.valid = false;
				return;
			}

			float t1, t2, sq_delta, over_2a;
			sq_delta = b*b - 4*a*c;

			if(sq_delta < EPS)
			{
				out.valid = false;
				return;
			}

			sq_delta = sqrt(sq_delta);
			over_2a = 1.0f / (2*a);
			t1 = (-b - sq_delta) * over_2a;
			t2 = (-b + sq_delta) * over_2a;

			//if t1 is positive, it is the closest
			//intersection
			if(t1 > EPS)
			{
				out.valid = true;
				out.t = t1;
				out.normal = glm::normalize( r(t1) - center );
				out.material = this->material;

				return;
			}

			if(t2 > EPS)
			{
				out.valid = true;
				out.t = t2;
				out.normal = glm::normalize( r(t2) - center );
				out.material = this->material;

				return;
			}

			out.valid = false;
			*/
		}
	}
}