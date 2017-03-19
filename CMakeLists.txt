cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Raytracer)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

#Headers
include_directories(include)

#Source files
file(GLOB SOURCES "src/*.cpp" 
					"src/Shapes/*.cpp" 
					"src/Lights/*.cpp"
					"src/Integrator/*.cpp")

add_executable(raytracer ${SOURCES})