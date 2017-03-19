#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "jsonHelper.h"
#include "geometry.h"

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
		 		glm::vec3 p, q, r;
				r = look - pos;
				q = up - glm::dot(up, r)*r;
				p = glm::cross(q, r);

				world2cam = glm::mat3(p, q, r);
				cam2world = glm::inverse(world2cam);

				w = d * tan(FOV * 0.5f);
				h = w / aspectRatio;
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