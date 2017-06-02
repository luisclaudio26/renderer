#include "../include/geometry.h"
#include <iostream>

namespace Renderer
{
	namespace Geometry
	{
		bool AABB::intersect(const Ray& r, float& t_min, float& t_max) const
		{
			//Taken from 
			//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
			//TODO: modify code so it uses max/min, which is faster.
			float tmin = (min[0] - r.o[0]) / r.d[0];
			float tmax = (max[0] - r.o[0]) / r.d[0];

			if (tmin > tmax) std::swap(tmin, tmax);

			float tymin = (min[1] - r.o[1]) / r.d[1];
			float tymax = (max[1] - r.o[1]) / r.d[1];

			if (tymin > tymax) std::swap(tymin, tymax);

			if ((tmin > tymax) || (tymin > tmax)) return false;

			if (tymin > tmin)
				tmin = tymin;

			if (tymax < tmax)
				tmax = tymax;

			float tzmin = (min[2] - r.o[2]) / r.d[2];
			float tzmax = (max[2] - r.o[2]) / r.d[2];

			if (tzmin > tzmax) std::swap(tzmin, tzmax);

			if ((tmin > tzmax) || (tzmin > tmax)) return false;

			if (tzmin > tmin)
				tmin = tzmin;

			if (tzmax < tmax)
				tmax = tzmax;

			return true; 
		}

		int AABB::maximumExtent() const
		{
			double longestAxis = 0;
			double longestExtent = this->max[0] - this->min[0];

			for(int i = 0; i < 3; i++)
				if( this->max[i] - this->min[i] > longestExtent )
				{
					longestAxis = i;
					longestExtent = this->max[i] - this->min[i];
				}

			return longestAxis;
		}
	}
}