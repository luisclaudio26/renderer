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

			//std::cout<<"\nPartitioning on "<<c<<" [axle = "<<axle<<"]\n";

			//put primitives in right or left node
			//TODO: for some reason, not all primitives are being
			//put in nodes.
			for(auto m = n.prim.begin(); m != n.prim.end(); ++m)
			{
				//float midpoint = ((*m)->bbox.p[axle] + (*m)->bbox.q[axle])*0.5f;
				
				if((*m)->bbox.min[axle] < c) n.l->prim.push_back( *m );
				if((*m)->bbox.max[axle] > c) n.r->prim.push_back( *m );

				/*
				if(midpoint >= c)
				{
					n.r->prim.push_back( *m );
					if((*m)->bbox.p[axle] < c) n.l->prim.push_back( *m );
				}
				else
				{
					n.l->prim.push_back( *m );
					if((*m)->bbox.q[axle] >= c) n.r->prim.push_back( *m );
				}*/

				//if(!any) std::cout<<"Primitive was sent to neither of the leaves!"<<std::endl;
			}

			/*			
			std::cout<<"Axis = "<<axle<<std::endl;
			std::cout<<"Primitives before: "<<n.prim.size()<<std::endl;
			std::cout<<"Primitives after: "<<n.l->prim.size()<<" on the left and "<<n.r->prim.size()<<" on the right";
			std::cout<<" (total = "<<n.l->prim.size()+n.r->prim.size()<<")\n";
			*/

			/*
			bool diff = n.prim.size() != n.l->prim.size()+n.r->prim.size();
			if(diff) std::cout<<"Here!!!"<<std::endl;*/

			//define new bounding boxes
			n.l->bbox.min = n.bbox.min; 
			n.l->bbox.max = n.bbox.max;
			n.l->bbox.max[axle] = c;

			n.r->bbox.min = n.bbox.min;	
			n.r->bbox.max = n.bbox.max;
			n.r->bbox.min[axle] = c;

			/*
			std::cout<<"First bounding box: "<<std::endl;
			std::cout<<glm::to_string(n.bbox.p)<<", "<<glm::to_string(n.bbox.q)<<std::endl;

			std::cout<<"New bounding boxes: "<<std::endl;
			std::cout<<glm::to_string(n.l->bbox.p)<<", "<<glm::to_string(n.l->bbox.q)<<std::endl;
			std::cout<<glm::to_string(n.r->bbox.p)<<", "<<glm::to_string(n.r->bbox.q)<<std::endl;
			*/

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

			std::cout<<"Bounding box: "<<glm::to_string(root.bbox.min)<<"\t"<<glm::to_string(root.bbox.max)<<std::endl;

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