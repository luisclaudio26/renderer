#include <iostream>
#include <fstream>
#include <vector>

#include "../3rdparty/json.hpp"
#include "../include/camera.h"
#include "../include/shape.h"

int main()
{
	std::fstream in("../data/spheres.json");
	nlohmann::json j;
	in >> j;

	Camera::pCamera cam = Camera::cameraFromJSON( j["camera"] );

	std::vector<Shape> shapes; nlohmann::json geometry = j["geometry"];
	for(auto s = geometry.begin(); s != geometry.end(); ++s)
	{
	}



	return 0;
}