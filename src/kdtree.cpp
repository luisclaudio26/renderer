#include "../include/kdtree.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <cfloat>

namespace Renderer
{
	namespace Scene
	{
		/*
		void kdTree::build(std::vector<TriFace*>& triangles, int depth)
		{
			//find bounding box for the whole scene
			float fmax = FLT_MAX;
			root.bbox.p = glm::vec3(fmax, fmax, fmax);
			root.bbox.q = glm::vec3(-fmax, -fmax, -fmax);
			
			for(auto tri = triangles.begin(); tri != triangles.end(); ++tri)
			{
				glm::vec3 v1 = (*tri)->vertex[0]; 
				glm::vec3 v2 = (*tri)->vertex[1];
				glm::vec3 v3 = (*tri)->vertex[2];

				root.bbox.p[0] = glm::min(root.bbox.p[0], glm::min(v1[0], glm::min(v2[0], v3[0])));
				root.bbox.p[1] = glm::min(root.bbox.p[1], glm::min(v1[1], glm::min(v2[1], v3[1])));
				root.bbox.p[2] = glm::min(root.bbox.p[2], glm::min(v1[2], glm::min(v2[2], v3[2])));

				root.bbox.q[0] = glm::max(root.bbox.q[0], glm::max(v1[0], glm::max(v2[0], v3[0])));
				root.bbox.q[1] = glm::max(root.bbox.q[1], glm::max(v1[1], glm::max(v2[1], v3[1])));
				root.bbox.q[2] = glm::max(root.bbox.q[2], glm::max(v1[2], glm::max(v2[2], v3[2])));
			}

			std::cout<<glm::to_string(root.bbox.p)<<", "<<glm::to_string(root.bbox.q)<<std::endl;

		}

		void kdTree::closestTriangle(const Ray& r, Intersection& out)
		{
			out.valid = false;
		}
		*/
	}
}