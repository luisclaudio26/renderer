#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>

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
using namespace std::chrono;

int main(int argc, char* args[])
{
	srand(time(NULL));
	
	std::fstream in( args[1] );
	nlohmann::json j;
	in >> j;

	Integrator::ptr renderer = IntegratorFactory::create( j["integrator"] );
	Scene::SceneManager::ptr scene(new Scene::SceneManager); renderer->addScene(scene);

	//camera
	Camera::ptr pCam = Camera::cameraFromJSON( j["camera"] );
	renderer->addCamera(pCam);

	//shapes
	nlohmann::json geometry = j["geometry"];
	for(auto s = geometry.begin(); s != geometry.end(); ++s)
	{
		Shape::ptr shape = ShapeFactory::create(*s);
		scene->addShape(shape);
	}

	scene->buildTree();

	//lighting
	nlohmann::json lighting = j["lights"];
	for(auto l = lighting.begin(); l != lighting.end(); ++l)
	{
		Light::ptr light = LightFactory::create(*l);
		scene->addLight(light);
	}


	high_resolution_clock::time_point tS = high_resolution_clock::now();
	renderer->render("../output/out.ppm");
	high_resolution_clock::time_point tE = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(tE - tS);
	std::cout<<"Rendered in "<<time_span.count()<<" s"<<std::endl;

	return 0;
}