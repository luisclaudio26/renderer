#include "../../include/Primitives/primPlane.h"

namespace Renderer
{
	namespace Shapes
	{
		PrimPlane::PrimPlane(glm::vec3 n, glm::vec4 c)
		{
			normal = n;
			center = c;
		}

		PrimPlane::PrimPlane()
		{
			normal = glm::vec3(0,0,0);
			center = glm::vec4(0,0,0,0);
		}
			
		void PrimPlane::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;
			float d_N = glm::dot(normal, r.d);

			if( fabs(d_N) < 0.00001 ) return;
			
			out.t = glm::dot(normal, glm::vec3(center) - r.o) / d_N;

			if(out.t <= 0.0f) return;

			out.valid = true;
			out.normal = normal;

			return;
		}
	}
}