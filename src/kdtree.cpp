#include "../include/kdtree.h"
#include <iostream>
#include <cfloat>
#include <algorithm>
#include <limits>
#include <stack>
#include <glm/gtx/string_cast.hpp>
#include "../include/geometry.h"

namespace Renderer
{
	namespace Scene
	{
		using namespace Geometry;

		#define COST_ISECT 80
		#define COST_TRAV 1
		#define EMPTY_BONUS 0.1

		#define START 0
		#define END 1

		typedef struct {
			float t;
			int primNum;
			int type;
		} Edge;

		void kdTree::buildNode(kdNode& n, int depth)
		{
			//stopping criterium
			if( n.primNum.size() < 10 || depth == 10 )
			{
				n.r = n.l = NULL;
				//std::cout<<"Reached leaf: "<<n.prim.size()<<std::endl;
				return;
			}

			int retries = 0, badRefines = 0;
			std::vector<Edge> edges[3];

			//choose split axis position for interior node
			glm::vec3 d = n.bbox.max - n.bbox.min;
			int bestAxis = -1, bestOffset = -1;
			float bestCost = std::numeric_limits<float>::max();
			float oldCost = COST_ISECT * n.primNum.size();
			float totalSA = 2.0f * ((d[0] * d[1]) + 
									(d[0] * d[2]) + 
									(d[1] + d[2]));
			float invTotalSA = 1.0f / totalSA;

			int axle = n.bbox.maximumExtent();

			retrySplit:

			//Initialize edges for axis
			for(int i = 0; i < n.primNum.size(); i++)
			{
				int p_id = n.primNum[i];
				Primitive* p = prim[p_id]; 
				Edge eS, eE;
				
				eS.t = p->bbox.min[axle]; 
				eE.t = p->bbox.max[axle];
				eS.primNum = eE.primNum = p_id;
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
			int nBelow = 0, nAbove = n.primNum.size();
			for(int i = 0; i < edges[axle].size(); i++)
			{
				//if we are in and END edge, this primitive
				//is not above it anymore, so we must decrease
				//this counter;
				if(edges[axle][i].type == END) --nAbove;

				float t = edges[axle][i].t;

				//compute surface area of child nodes when
				//we split it at edgeT
				if(t > n.bbox.min[axle] && t < n.bbox.max[axle])
				{
					//surface area of the splitted bounding boxes
					int otherAxle0 = (axle + 1) % 3, otherAxle1 = (axle + 2) % 3;
					float aboveSA = 2 * (d[otherAxle1]*d[otherAxle0] +
										(n.bbox.max[axle] - t) * (d[otherAxle1] + d[otherAxle0]));
					float belowSA = 2 * (d[otherAxle1]*d[otherAxle0] +
										(t - n.bbox.min[axle]) * (d[otherAxle1] + d[otherAxle0]));

					//compute cost for split at i-th edge
					float pBelow = belowSA * invTotalSA;
					float pAbove = aboveSA * invTotalSA;
					float eb = (nAbove == 0 || nBelow == 0) ? EMPTY_BONUS : 0.0f;
					float cost = COST_TRAV + 
									COST_ISECT * (1 - eb) * (pBelow * nBelow + pAbove * nAbove);

					//std::cout<<"pBelow = "<<pBelow<<", pAbove = "<<pAbove<<std::endl;

					if(cost < bestCost)
					{
						bestCost = cost;
						bestAxis = axle;
						bestOffset = i;

						/*
						std::cout<<"Best cost = "<<bestCost;
						std::cout<<", best axis = "<<bestAxis;
						std::cout<<", best offset = "<<bestOffset<<std::endl;
						*/
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
			if(!(nBelow == n.primNum.size() && nAbove == 0))
				std::cout<<"Something wrong!"<<std::endl;
			*/

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
			if(bestCost > oldCost) ++badRefines;

			if( (bestCost > 4 * oldCost && n.primNum.size() < 16) || bestAxis == -1 || badRefines == 3)
			{
				n.l = n.r = NULL;
				return;
			}

			//Notice that it is possible (and it will occur often) for
			//a primitive to be in two different nodes. This is no problem
			//a priori, but can cause race conditions, and also will make
			//the kd-tree redudant.
			n.r = new kdNode; n.l = new kdNode;

			//put primitives in right or left node
			//TODO: copying stuff and allocating them
			//is bad! We should have ONE structure holding
			//primitives and leafs store indices to it.
			
			/*
			for(int i = 0; i < bestOffset; i++)
				if(edges[bestAxis][i].type == START)
					n.r->primNum.push_back( edges[bestAxis][i].primNum );
			for(int i = bestOffset + 1; i < edges[bestAxis].size(); i++)
				if(edges[bestAxis][i].type == END)
					n.l->primNum.push_back( edges[bestAxis][i].primNum );
			*/

			float tSplit = edges[bestAxis][bestOffset].t;
			for(auto m = n.primNum.begin(); m != n.primNum.end(); ++m)
			{
				Primitive* p = this->prim[*m];

				if(p->bbox.min[axle] < tSplit)
					n.l->primNum.push_back( *m );

				if(p->bbox.max[axle] > tSplit)
					n.r->primNum.push_back( *m );
			}

			/*
			std::cout<<"Box: "<<glm::to_string(n.bbox.min)<<"\n"<<glm::to_string(n.bbox.max)<<std::endl;
			std::cout<<"c = "<<tSplit<<", axis = "<<bestAxis<<std::endl;
			std::cout<<"\tN prim left/right: "<<n.l->primNum.size()<<", "<<n.r->primNum.size()<<std::endl;
			*/

			//define new bounding boxes
			n.l->bbox.min = n.bbox.min;
			n.l->bbox.max = n.bbox.max;
			n.l->bbox.max[bestAxis] = tSplit;

			n.r->bbox.min = n.bbox.min;	
			n.r->bbox.max = n.bbox.max;
			n.r->bbox.min[bestAxis] = tSplit;

			n.axis = bestAxis;
			n.t = tSplit;

			//recursively build nodes
			buildNode(*(n.r), depth+1);
			buildNode(*(n.l), depth+1);
		}

		void kdTree::build(std::vector<Primitive*>&& prim)
		{
			//copy primitives
			this->prim = prim;
			this->maxDepth = (int)std::round(8.0 + log2(this->prim.size()));

			//find bounding box for the whole scene, and
			//also push the indices of primitives to the Root
			this->root.bbox.max = glm::vec3(FLT_MIN, FLT_MIN, FLT_MIN);
			this->root.bbox.min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);

			int p_id = 0;
			for(auto r = this->prim.begin(); r != this->prim.end(); ++r)
			{
				(*r)->defineBBox();
				for(int i = 0; i < 3; i++)
				{
					this->root.bbox.max[i] = glm::max(this->root.bbox.max[i], (*r)->bbox.max[i]);
					this->root.bbox.min[i] = glm::min(this->root.bbox.min[i], (*r)->bbox.min[i]);
				}

				this->root.primNum.push_back(p_id++);
			}

			//launch kd tree building method for root node
			buildNode(this->root);
		}

		typedef struct {
			const kdNode* n;
			float tMin, tMax;
		} NodeToDo;

		void kdTree::hit(const Ray& r, Intersection& out) const
		{
			//assumes out.t = Infinity and out.valid = false
			//in the first call
			float tmin, tmax;
			if( !root.bbox.intersect(r, tmin, tmax) )
				return;

			glm::vec3 invDir(1.0f / r.d[0], 1.0f / r.d[1], 1.0f / r.d[2]);
			
			std::stack<NodeToDo> todo; 
			todo.push( (NodeToDo){&root, tmin, tmax} );

			while(!todo.empty())
			{
				const NodeToDo& node = todo.top();
				todo.pop();

				//PBRT uses this, but I don't know what's tMax:
				//if(ray.tMax < tMin) break;

				if(node.n->l != NULL && node.n->r != NULL)
				{
					int axis = node.n->axis;
					float tPlane = (node.n->t - r.o[axis]) * invDir[axis];

					//Select who will be traversed next
					NodeToDo near, far;
					bool leftFirst = (r.o[axis] < node.n->t) || (r.o[axis] == node.n->t && r.d[axis] <= 0);
					
					if(leftFirst)
					{
						near = (NodeToDo){node.n->l, node.tMin, tPlane};
						far = (NodeToDo){node.n->r, tPlane, node.tMax};
					}
					else
					{
						near = (NodeToDo){node.n->r, node.tMin, tPlane};
						far = (NodeToDo){node.n->l, tPlane, node.tMax};
					}
					
					//enqueue near and/or far
					if(tPlane > node.tMax || tPlane <= 0) //ray won't hit Far box
						todo.push(near);
					else if(tPlane < node.tMin) //ray won't hit Near box
						todo.push(far);
					else //visit near first, then far
					{
						todo.push(far);
						todo.push(near);
					}
				}
				else
				{
					//Inside leaf node: test against primitives.
					for(auto p_id = node.n->primNum.begin(); p_id != node.n->primNum.end(); ++p_id)
					{
						Primitive* p = this->prim[*p_id];
						Intersection I; p->intersect(r, I);

						//we consider only intersections in the positive direction
						//of the ray; it is useless (in this context) to consider
						//intersection in the negative side! (this implies intersection
						//with things behind the origin of the ray).
						if(I.valid && I.t > 0.0f && I.t < out.t) out = I;
					}
				}
			}
		}
	}
}