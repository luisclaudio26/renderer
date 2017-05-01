#include "../../include/Primitives/triangle.h"

namespace Renderer
{
	namespace Shapes
	{
		Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
		{
			vertex[0] = v1;
			vertex[1] = v2;
			vertex[2] = v3;
		}

		Triangle::Triangle()
		{
			vertex[0] = vertex[1] = vertex[2] = glm::vec3(0,0,0);
		}

		void Triangle::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;

			// Möller-Trumbore algorithm, as described in
			// https://www.scratchapixel.com/lessons/3d-basic-rendering/
			// ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection		
			glm::vec3 v0v1 = vertex[1] - vertex[0]; 
			glm::vec3 v0v2 = vertex[2] - vertex[0];
			glm::vec3 pvec = glm::cross(r.d, v0v2);
			float det = glm::dot(v0v1, pvec);

			//backface culling
			if( det < 0.0000001 ) return;
			float invDet = 1 / det;

			glm::vec3 tvec = r.o - vertex[0];
			float u = glm::dot(tvec, pvec) * invDet;
			if (u < 0 || u > 1) return;

			glm::vec3 qvec = glm::cross(tvec, v0v1);
			float v = glm::dot(r.d, qvec) * invDet;
			if (v < 0 || u + v > 1) return;

			out.t = glm::dot(v0v2, qvec) * invDet;
			out.normal = glm::cross(v0v1, v0v2);
			out.valid = true;
		}
	}
}