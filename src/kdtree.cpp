#include "../include/kdtree.h"
#include <iostream>
#include <cfloat>
#include <glm/gtx/string_cast.hpp>
#include "../include/geometry.h"

namespace Renderer
{
	namespace Scene
	{
		using namespace Geometry;

		float centroid(const std::vector<Primitive*>& prim, int axle)
		{
			//not a real centroid, cause centroid of each primitive
			//is not in fact calculated (we use the q point instead).
			float sum = 0.0f;
			for(auto p = prim.begin(); p != prim.end(); ++p)
				sum += (*p)->bbox.q[axle];
			return sum / prim.size();
		}

		void buildNode(kdNode& n, int depth = 0, int axle = 0)
		{
			//stopping criterium
			if(depth == 8)
			{
				n.r = n.l = NULL;
				n.split = std::numeric_limits<float>::quiet_NaN();

				//std::cout<<"Reached depth 8! Number of primitives: "<<n.prim.size()<<std::endl;
				return;
			}

			//Notice that it is possible (and it will occur often) for
			//a primitive to be in two different nodes. This is no problem
			//a priori, but can cause race conditions, and also will make
			//the kd-tree redudant.
			float c = centroid(n.prim, axle);
			n.r = new kdNode; n.l = new kdNode;

			//put primitives in right or left node
			//TODO: for some reason, not all primitives are being
			//put in nodes.
			for(auto m = n.prim.begin(); m != n.prim.end(); ++m)
			{
				if( (*m)->bbox.q[axle] < c )
					n.l->prim.push_back( *m );

				if( (*m)->bbox.p[axle] >= c )
					n.r->prim.push_back( *m );
			}

			//define new bounding boxes
			n.l->bbox.q = n.bbox.q;
			n.l->bbox.p = n.bbox.p; n.l->bbox.p[axle] = c;

			n.r->bbox.p = n.bbox.p;
			n.r->bbox.q = n.bbox.q; n.r->bbox.q[axle] = c;

			/*
			std::cout<<"First bounding box: "<<std::endl;
			std::cout<<glm::to_string(n.bbox.p)<<", "<<glm::to_string(n.bbox.q)<<std::endl;

			std::cout<<"New bounding boxes: "<<std::endl;
			std::cout<<glm::to_string(n.l->bbox.p)<<", "<<glm::to_string(n.l->bbox.q)<<std::endl;
			std::cout<<glm::to_string(n.r->bbox.p)<<", "<<glm::to_string(n.r->bbox.q)<<std::endl;
			*/

			//define split point for this node
			n.split = c;

			//recursively build nodes
			int nextAxle = (axle + 1) % 3;
			buildNode(*(n.r), depth+1, nextAxle);
			buildNode(*(n.l), depth+1, nextAxle);



			/*
			std::cout<<"Primitive count: "<<n.prim.size()<<std::endl;
			std::cout<<"Primitives in Left: "<<n.l->prim.size()<<std::endl;
			std::cout<<"Primitives in Right: "<<n.r->prim.size()<<std::endl;
			*/
		}

		void kdTree::build(const std::vector<Primitive*>& prim, int depth)
		{
			this->root.bbox.p = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);
			this->root.bbox.q = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);

			//find bounding box for the whole scene
			for(auto r = prim.begin(); r != prim.end(); ++r)
			{
				(*r)->defineBBox();
				for(int i = 0; i < 3; i++)
				{
					this->root.bbox.p[i] = glm::max(this->root.bbox.p[i], (*r)->bbox.p[i]);
					this->root.bbox.q[i] = glm::min(this->root.bbox.q[i], (*r)->bbox.q[i]);
				}
			}

			//launch kd tree building method for root node
			this->root.prim = prim; //TODO: how to avoid copies?!
			buildNode(this->root);
		}

		void kdTree::intersect(const Ray& r, Intersection& out)
		{
			out.valid = false;
		}
	}
}