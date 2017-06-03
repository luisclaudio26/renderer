#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "primitive.h"
#include "../BxDF/bxdf.h"

namespace Renderer
{
	namespace Shapes
	{
		class Triangle : public Primitive
		{
		public:
			glm::vec3 vertex[3];

			Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
			Triangle();
			
			void intersect(const Ray& r, Intersection& out, bool tryBackfaceCulling = false) override;
			void defineBBox() override;

			Triangle& operator*(const glm::mat4& T);
		};
	}
}

#endif