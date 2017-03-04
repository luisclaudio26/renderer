#include <iostream>
#include <fstream>
#include "../3rdparty/json.hpp"
#include "../include/camera.h"

int main()
{
	std::fstream in("../data/spheres.json");
	nlohmann::json j;
	in >> j;

	Camera cam; Camera::cameraFromJSON( j["camera"], cam );



	return 0;
}