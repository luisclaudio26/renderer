#include "../../include/Shapes/meshobj.h"
#include "../../include/BxDF/bxdf.h"
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <iostream>

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		std::string MeshOBJ::str()
		{
			std::string out("[.OBJ Mesh] { ");

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
					Triangle face;

					//define geometry
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

			this->transformed = false;
		}

		void MeshOBJ::getPrimitives(std::vector<Primitive*>& out)
		{
			//Transform primitives if they were not transformed yet
			for(auto s = shapes.begin(); s != shapes.end(); ++s)
				for(auto t = s->faces.begin(); t != s->faces.end(); ++t)
				{
					if(!transformed)
						(*t) = (*t) * this->model2world;

					out.push_back( &(*t) );
				}

			transformed = true;
		}

		void MeshOBJ::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;
			out.t = std::numeric_limits<float>::max();

			for(auto s = shapes.begin(); s != shapes.end(); ++s)
				for(auto f = s->faces.begin(); f != s->faces.end(); ++f)
				{
					Intersection I; f->intersect(r, I);
					if(I.valid && I.t < out.t) out = I;
				}
		}

	}
}