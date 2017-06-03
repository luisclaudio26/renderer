#include "../include/kdtree.h"
#include <iostream>
#include <cfloat>
#include <algorithm>
#include <limits>
#include <glm/gtx/string_cast.hpp>
#include "../include/geometry.h"

namespace Renderer
{
	namespace Scene
	{
		using namespace Geometry;

		#define COST_ISECT 20
		#define COST_TRAV 1
		#define EMPTY_BONUS 0.1

		#define START false
		#define END true

		typedef struct {
			float t;
			int primNum;
			bool type;
		} Edge;

		float bestSplit(const AABB& bbox, const std::vector<Primitive*>& prim, int& axle)
		{
			axle = bbox.maximumExtent();
			int retries = 0, badRefines = 0;
			std::vector<Edge> edges[3];

			glm::vec3 d = bbox.max - bbox.min;
			int bestAxis = -1, bestOffset = -1;
			float bestCost = std::numeric_limits<float>::max();
			float oldCost = COST_ISECT * prim.size();
			float totalSA = 2.0f * d[0] * d[1] * d[2];
			float invTotalSA = 1.0f / totalSA;

			//TODO: no need to create/sort edges for all three
			//axis. Do this only if we retry for some reason
			//(which should be rare).
			retrySplit:

			//Now sort the bounding boxes so to choose the split point.
			for(int i = 0; i < prim.size(); i++)
			{
				Primitive* p = prim[i]; Edge eS, eE;
				
				eS.t = p->bbox.min[axle]; eE.t = p->bbox.max[axle];
				eS.primNum = eE.primNum = i;
				eS.type = START; eE.type = END;
				
				edges[axle].push_back( eS );
				edges[axle].push_back( eE );
			}

			//sort edges
			std::sort( edges[axle].begin(), edges[axle].end(), 
						[](const Edge& lhs, const Edge& rhs) -> bool {
							if(lhs.t == rhs.t)
								return (int)lhs.type < (int)rhs.type;
							else
								return lhs.t < rhs.t;
						});

			//compute costs of all splits for axis to find best
			int nBelow = 0, nAbove = prim.size();
			for(int i = 0; i < edges[axle].size(); i++)
			{
				//if we are in and END edge, this primitive
				//is not above it anymore, so we must decrease
				//this counter;
				if(edges[axle][i].type == END) --nAbove;

				float t = edges[axle][i].t;

				//compute surface area of child nodes when
				//we split it at edgeT
				if(t >= bbox.min[axle] && t <= bbox.max[axle])
				{
					//surface area of the splitted bounding boxes
					int otherAxle0 = (axle + 1) % 3, otherAxle1 = (axle + 2) % 3;
					float aboveSA = 2 * (d[otherAxle1]*d[otherAxle0] +
										(bbox.max[axle] - t) * (d[otherAxle1] + d[otherAxle0]));
					float belowSA = 2 * (d[otherAxle1]*d[otherAxle0] +
										(t - bbox.min[axle]) * (d[otherAxle1] + d[otherAxle0]));

					//compute cost for split at i-th edge
					float pBelow = belowSA * invTotalSA;
					float pAbove = aboveSA * invTotalSA;
					float eb = (nAbove == 0 || nBelow == 0) ? EMPTY_BONUS : 0.0f;
					float cost = COST_TRAV + 
									COST_ISECT * (1 - eb) * (pBelow * nBelow + pAbove * nAbove);

					if(cost < bestCost)
					{
						bestCost = cost;
						bestAxis = axle;
						bestOffset = i;
					}
				}

				//if we we are in a START edge, the next
				//edge will be an END one; this means we
				//must increase the number of primitives
				//below it, because the next edge will
				//be above the current primitive.
				if(edges[axle][i].type == START) ++nBelow;
			}

			/*
			std::cout<<"bestCost = "<<bestCost<<std::endl;
			std::cout<<"bestAxis = "<<bestAxis<<std::endl;
			std::cout<<"bestOffset = "<<bestOffset<<std::endl;
			*/
			//retry if there's possible split for this axis.
			//this should happen when node is too small in this
			//axis, compared to the primitives inside it.
			if(bestAxis == -1 && retries < 2) 
			{
				++retries;
				axle = (axle + 1) % 3;
				goto retrySplit;
			}

			//if this split is worst then simply traversing
			//the primitives, stop.
			if(bestCost > oldCost)
				return std::numeric_limits<float>::quiet_NaN();

			return edges[bestAxis][bestOffset].t;
		}

		void buildNode(kdNode& n, int depth = 0)
		{
			//stopping criterium
			if( n.prim.size() < 10 || depth == 10 )
			{
				n.r = n.l = NULL;
				//std::cout<<"Reached leaf: "<<n.prim.size()<<std::endl;
				return;
			}

			//Notice that it is possible (and it will occur often) for
			//a primitive to be in two different nodes. This is no problem
			//a priori, but can cause race conditions, and also will make
			//the kd-tree redudant.
			int axle;
			float c = bestSplit(n.bbox, n.prim, axle);
			n.r = new kdNode; n.l = new kdNode;

			//if c == -1, then it is better not to split
			//this node!
			if(c != c)
			{
				n.r = n.l = NULL;
				return;
			}

			//put primitives in right or left node
			//TODO: copying stuff and allocating them
			//is bad! We should have ONE structure holding
			//primitives and leafs store indices to it.
			for(auto m = n.prim.begin(); m != n.prim.end(); ++m)
			{
				if((*m)->bbox.min[axle] < c) n.l->prim.push_back( *m );
				if((*m)->bbox.max[axle] > c) n.r->prim.push_back( *m );
			}

			std::cout<<" c = "<<c<<std::endl;
			std::cout<<"N prim left/right: "<<n.l->prim.size()<<", "<<n.r->prim.size()<<std::endl;

			//define new bounding boxes
			n.l->bbox.min = n.bbox.min; 
			n.l->bbox.max = n.bbox.max;
			n.l->bbox.max[axle] = c;

			n.r->bbox.min = n.bbox.min;	
			n.r->bbox.max = n.bbox.max;
			n.r->bbox.min[axle] = c;

			//recursively build nodes
			buildNode(*(n.r), depth+1);
			buildNode(*(n.l), depth+1);
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