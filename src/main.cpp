#include <iostream>
#include <fstream>
#include <vector>

#include "../3rdparty/json.hpp"
#include "../include/camera.h"
#include "../include/shape.h"
#include "../include/shapeFactory.h"

int main()
{
	std::fstream in("../data/spheres.json");
	nlohmann::json j;
	in >> j;

	Camera::ptr pCam = Camera::cameraFromJSON( j["camera"] );

	std::vector<Shape::ptr> shapes; nlohmann::json geometry = j["geometry"];
	for(auto s = geometry.begin(); s != geometry.end(); ++s)
	{
		shapes.push_back( ShapeFactory::create(*s) );
		std::cout<<shapes.back()->str()<<std::endl;
	}


	return 0;
}