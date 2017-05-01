cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(SET CMP0015 NEW)
project(Raytracer)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -g")

#Headers
include_directories(include)

#Source files
file(GLOB SOURCES "src/*.cpp" 
					"src/Shapes/*.cpp" 
					"src/Lights/*.cpp"
					"src/Integrator/*.cpp"
					"src/Spectra/*.cpp"
					"src/BxDF/*.cpp"
					"src/Primitives/*.cpp")

#Link static libraries
link_directories(3rdparty)

add_executable(raytracer ${SOURCES})
target_link_libraries(raytracer tinyobjloader)
