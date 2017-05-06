#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "jsonHelper.h"
#include "geometry.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

namespace Renderer
{
	namespace Cameras
	{
		class Camera
		{
		public:
			typedef std::shared_ptr<Camera> ptr;
			
			//------------------
			//------ data ------
			//------------------
			glm::vec3 pos;
			glm::vec3 up, look;

			float aspectRatio, FOV, d; //distance between image plane and camera center
			int hRes, vRes; //horizontal and vertical resolution of film
			float w, h; //Film width and height in world space

			glm::mat3 cam2world, world2cam;

			//---------------------
			//------ methods ------
			//---------------------
			Camera(const glm::vec3& pos, const glm::vec3 up,
						const glm::vec3& look, float aspectRatio,
						float FOV, float d, int hRes, int vRes)
					: pos(pos), up(up), look(look), aspectRatio(aspectRatio),
					  FOV(FOV), hRes(hRes), vRes(vRes), d(d)
		 	{
		 		//Don't forget that look-at (r) points to the back of the camera!
		 		glm::vec3 p, q, r;

				r = glm::normalize(look - pos);
				q = glm::normalize(up - glm::dot(up, r)*r);
				p = glm::cross(r, q);

				world2cam = glm::mat3(p, q, r);
				cam2world = glm::inverse(world2cam);

				//TODO: FILM CAN'T BE RESIZED AS FUNCTION OF
				//FILM DISTANCE! It makes us lose the "zooming"
				//effect of the film plane distance
				h = 1.0f; w = aspectRatio;
		 	}

			void getRay(float u, float v, Geometry::Ray& out);

			//---------------------------
			//------ Static stuff -------
			//---------------------------
			static ptr cameraFromJSON(const nlohmann::json& in);
		};
	}
}

#endif