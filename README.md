# Luis' Path-tracer

<img src="https://raw.githubusercontent.com/luisclaudio26/renderer/master/output/softShadowBunny.png" width="400"> <img src="https://raw.githubusercontent.com/luisclaudio26/renderer/master/output/coolDragon.png" width="400">

Stanford bunny and dragon, rendered with direct illumination only, both with original size of 1024x768. Bunny took ~5s to render and Dragon ~30s.

 <img src="https://raw.githubusercontent.com/luisclaudio26/renderer/master/output/cornellBox.png" width="800">
Cornell box with bunny and sphere, 1024x768, 50spp. Took about 430s to render.

## Overview
This is my first attempt to create a renderer system with support to multiple techniques of light transport simulation. I started this project with the intention of following verbatim the construction of PBRT as described in the book Physically-Based Rendering, but soon I realized that it was better to create a simpler, smaller project which covered the most fundamental techniques, and then pass on to a more complex (and better implemented) system.

I make use of C++11 STL (smart pointers, <algorithm> algos and the usual containers) and GLM for vector/matrix operations.

## What it does now

The renderer currently handles the following:

- Integration: Direct illumination, Path-tracing
- Lights: Point lights, plane area lights
- Geometry: Spheres, planes, triangle meshes
- Materials: Lambertian, and a Specular BRDF I designed so to have different tests, but it's not that good/correct
- Camera: Pinhole
- Acceleration: kd-trees using SAH

## What it shall do soon

I'm working hard to have the following working in the next 30 or 40 days:

- Lights: Eliminate the distinction between lights and meshes, and just add an emission profile to meshes
- Acceleration: kd-tree traversal in GPU using CUDA
