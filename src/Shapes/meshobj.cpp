#include "../../include/Shapes/meshobj.h"
#include <cmath>
#include <iostream>

//#define TINYOBJLOADER_IMPLEMENTATION

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		std::string MeshOBJ::str()
		{
			std::string s("[.OBJ Mesh] { ");

			tinyobj::shape_t& S = this->shapes[0];
			int attrib_offset = 0;
			for(int i = 0; i < S.mesh.num_face_vertices.size(); ++i)
			{
				int fv = S.mesh.num_face_vertices[i];

				for(int j = 0; j < fv; j++)
				{
					tinyobj::index_t index = S.mesh.indices[attrib_offset+j];

					float vx = this->attrib.vertices[3*index.vertex_index + 0];
					float vy = this->attrib.vertices[3*index.vertex_index + 1];
					float vz = this->attrib.vertices[3*index.vertex_index + 2];

					s += std::to_string(vx);
					s += ", ";
					s += std::to_string(vy);
					s += ", ";
					s += std::to_string(vz);
					s += ",\n";
				}
				attrib_offset += fv;
			} 

			return s;
		}

		void MeshOBJ::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;
			return;
		}
	}
}