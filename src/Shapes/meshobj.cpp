#include "../../include/Shapes/meshobj.h"
#include "../../include/BxDF/bxdf.h"
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/transform.hpp>
#include <cmath>
#include <iostream>

namespace Renderer
{
	namespace Shapes
	{
		using namespace Geometry;

		/*
		static bool intersectTriangle(const TriFace& tri, const Ray& r, float& t, glm::vec3& normal)
		{
			// Möller-Trumbore algorithm, as described in
			// https://www.scratchapixel.com/lessons/3d-basic-rendering/
			// ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection		
			glm::vec3 v0v1 = tri.vertex[1] - tri.vertex[0]; 
			glm::vec3 v0v2 = tri.vertex[2] - tri.vertex[0];
			glm::vec3 pvec = glm::cross(r.d, v0v2);
			float det = glm::dot(v0v1, pvec);

			//backface culling
			if( det < 0.0000001 ) return false;
			float invDet = 1 / det;

			glm::vec3 tvec = r.o - tri.vertex[0];
			float u = glm::dot(tvec, pvec) * invDet;
			if (u < 0 || u > 1) return false;

			glm::vec3 qvec = glm::cross(tvec, v0v1);
			float v = glm::dot(r.d, qvec) * invDet;
			if (v < 0 || u + v > 1) return false;

			t = glm::dot(v0v2, qvec) * invDet;
			normal = glm::cross(v0v1, v0v2);

			return true;
		} */

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
					Triangle face;

					//define geometry
					for(int v_id = 0; v_id < f; v_id++)
					{
						tinyobj::index_t v = s.mesh.indices[attrib_offset + v_id];

						float vx = attrib.vertices[3*v.vertex_index + 0];
						float vy = attrib.vertices[3*v.vertex_index + 1];
						float vz = attrib.vertices[3*v.vertex_index + 2];

						glm::mat4 rot = glm::rotate(glm::mat4(1.0f), 0.96f, glm::vec3(0.0f, 1.0f, 0.0f));
						glm::vec4 v_ = rot * glm::vec4(vx, vy, vz, 1.0f);

						face.vertex[v_id] = glm::vec3(v_[0], v_[1], v_[2]);
					}

					this->shapes.back().faces.push_back(face);
					attrib_offset += f;
				}
			}
		}

		void MeshOBJ::getPrimitives(std::vector<Primitive*>& out)
		{
			for(auto s = shapes.begin(); s != shapes.end(); ++s)
				for(auto t = s->faces.begin(); t != s->faces.end(); ++t)
					out.push_back( &(*t) );
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

			//TODO: Implement this the proper way (reading material from .mtl file)
			/*
			Lambertian *L = new Lambertian;
			L->color = glm::vec3(1.0, 0.0, 0.0);
			out.material = BxDF::BRDF::ptr(L);
			*/
		}

	}
}