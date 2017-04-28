#include "../../include/Shapes/meshobj.h"
#include <glm/gtx/intersect.hpp>
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
			std::string out("[.OBJ Mesh] { ");

			/*
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
			}*/

			for(auto s = shapes.begin(); s != shapes.end(); ++s)
			{
				for(auto f = s->faces.begin(); f != s->faces.end(); ++f)
				{
					out += "[";
					out += glm::to_string(f->vertex[0]);
					out += ", ";
					out += glm::to_string(f->vertex[1]);
					out += ", ";
					out += glm::to_string(f->vertex[2]);
					out += "], ";
				}
			}

			return out + "}\n";
		}

		MeshOBJ::MeshOBJ(const std::vector<tinyobj::shape_t>& shapes, const tinyobj::attrib_t& attrib)
		{
			for(int s_id = 0; s_id < shapes.size(); ++s_id)
			{
				//create a new shape at the tail
				this->shapes.emplace_back();
				
				const tinyobj::shape_t& s = shapes[s_id];
				int attrib_offset = 0;

				for(int f_id = 0; f_id < s.mesh.num_face_vertices.size(); ++f_id)
				{
					int f = s.mesh.num_face_vertices[f_id];
					TriFace face;

					for(int v_id = 0; v_id < f; v_id++)
					{
						tinyobj::index_t v = s.mesh.indices[attrib_offset + v_id];

						float vx = attrib.vertices[3*v.vertex_index + 0];
						float vy = attrib.vertices[3*v.vertex_index + 1];
						float vz = attrib.vertices[3*v.vertex_index + 2];

						face.vertex[v_id] = glm::vec3(vx, vy, vz);
					}

					this->shapes.back().faces.push_back(face);
					attrib_offset += f;
				}
			}
		}

		void MeshOBJ::intersect(const Ray& r, Intersection& out)
		{
			for(auto s = shapes.begin(); s != shapes.end(); ++s)
			{
				for(auto f = s->faces.begin(); f != s->faces.end(); ++f)
				{
					glm::vec3 inter_coord;
					bool res = glm::intersectRayTriangle(r.o, r.d, f->vertex[0], 
														f->vertex[1], f->vertex[2], inter_coord);
					if(res)
						std::cout<<(inter_coord[0] - r.o[0])/r.d[0]<<std::endl;
				}
			}

			out.valid = false;
			return;
		}


	}
}