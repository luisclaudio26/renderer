#include <iostream>
#include <fstream>
#include <vector>

#include "../3rdparty/json.hpp"
#include "../include/camera.h"

#include "../include/Integrator/integrator.h"
#include "../include/Integrator/integratorFactory.h"

#include "../include/Shapes/shape.h"
#include "../include/Shapes/shapeFactory.h"

#include "../include/Lights/light.h"
#include "../include/Lights/lightFactory.h"

using namespace Renderer;
using namespace Shapes;
using namespace Lighting;
using namespace Integration;
using namespace Cameras;

int main()
{
	std::fstream in("../data/spheres.json");
	nlohmann::json j;
	in >> j;

	//camera
	Camera::ptr pCam = Camera::cameraFromJSON( j["camera"] );

	//shapes
	std::vector<Shape::ptr> shapes; nlohmann::json geometry = j["geometry"];
	for(auto s = geometry.begin(); s != geometry.end(); ++s)
	{
		shapes.push_back( ShapeFactory::create(*s) );
		std::cout<<shapes.back()->str()<<std::endl;
	}

	//lighting
	std::vector<Light::ptr> lights; nlohmann::json lighting = j["lights"];
	for(auto l = lighting.begin(); l != lighting.end(); ++l)
	{
		lights.push_back( LightFactory::create(*l) );
		std::cout<<lights.back()->str()<<std::endl;
	}

	//spit image out!
	Integrator::ptr renderer = IntegratorFactory::create( j["integrator"] );

	return 0;
}