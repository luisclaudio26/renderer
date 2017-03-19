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

	Integrator::ptr renderer = IntegratorFactory::create( j["integrator"] );

	//camera
	Camera::ptr pCam = Camera::cameraFromJSON( j["camera"] );
	renderer->addCamera(pCam);

	//shapes
	nlohmann::json geometry = j["geometry"];
	for(auto s = geometry.begin(); s != geometry.end(); ++s)
	{
		Shape::ptr shape = ShapeFactory::create(*s);
		renderer->addShape(shape);
	}

	//lighting
	nlohmann::json lighting = j["lights"];
	for(auto l = lighting.begin(); l != lighting.end(); ++l)
	{
		Light::ptr light = LightFactory::create(*l);
		renderer->addLight(light);
	}

	renderer->render("../output/out.ppm");

	return 0;
}