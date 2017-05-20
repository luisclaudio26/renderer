#include "../../include/Primitives/primSphere.h"

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		void PrimSphere::defineBBox()
		{
			//this is not the tightest bounding box
			bbox.max = glm::vec3(center[0]+radius, center[1]+radius, center[2]+radius);
			bbox.min = glm::vec3(center[0]-radius, center[1]-radius, center[2]-radius);
		}

		void PrimSphere::intersect(const Ray& r, Intersection& out)
		{
			//I don't know where to move this.
			const float EPS = 0.0001;
			out.valid = false;

			glm::vec3 center = glm::vec3(this->center);

			float a = glm::dot(r.d, r.d);
			float b = 2.0f * glm::dot( r.d, r.o - center );
			float c = glm::dot(center, center) - 2.0f * glm::dot(center, r.o) + glm::dot(r.o, r.o) - radius*radius;

			//Neither this
			if( fabs(a) < EPS ) return;

			float t1, t2, sq_delta, over_2a;
			sq_delta = b*b - 4*a*c;

			if(sq_delta < EPS) return;

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
		}

	}
}