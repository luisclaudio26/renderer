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
			//TODO: Centroid() is computing NaN splits!
			float sum = 0.0f;
			
			for(auto p = prim.begin(); p != prim.end(); ++p)
				sum += ((*p)->bbox.min[axle] + (*p)->bbox.max[axle])*0.5f;
			
			if(prim.size() == 0)
				std::cout<<"No primitive to calculate centroid!"<<std::endl;

			return sum / prim.size();
		}

		void buildNode(kdNode& n, int depth = 0, int axle = 0)
		{
			//stopping criterium
			if( n.prim.size() < 10 || depth == 6 )
			{
				n.r = n.l = NULL;
				//std::cout<<"Reached leaf: "<<n.prim.size()<<std::endl;
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
				if((*m)->bbox.min[axle] < c) n.l->prim.push_back( *m );
				if((*m)->bbox.max[axle] > c) n.r->prim.push_back( *m );
			}

			//define new bounding boxes
			n.l->bbox.min = n.bbox.min; 
			n.l->bbox.max = n.bbox.max;
			n.l->bbox.max[axle] = c;

			n.r->bbox.min = n.bbox.min;	
			n.r->bbox.max = n.bbox.max;
			n.r->bbox.min[axle] = c;

			//recursively build nodes
			int nextAxle = (axle + 1) % 3;
			buildNode(*(n.r), depth+1, nextAxle);
			buildNode(*(n.l), depth+1, nextAxle);
		}

		void kdTree::build(const std::vector<Primitive*>& prim)
		{
			this->root.bbox.max = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);
			this->root.bbox.min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);

			//find bounding box for the whole scene
			for(auto r = prim.begin(); r != prim.end(); ++r)
			{
				(*r)->defineBBox();
				for(int i = 0; i < 3; i++)
				{
					this->root.bbox.max[i] = glm::max(this->root.bbox.max[i], (*r)->bbox.max[i]);
					this->root.bbox.min[i] = glm::min(this->root.bbox.min[i], (*r)->bbox.min[i]);
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