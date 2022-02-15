# basicRaytracer
I'm writing a ray-tracer!

Breakdown 
-
I wanted to learn C++ and Object-oriented programming, so I'm following a guide to write a small ray-tracer using SDL2 and native C++ libraries. 
I plan to eventually branch out and build on my own features such as new shapes, materials and physically based renders. 
Link to the tutorial: https://github.com/QuantitativeBytes/qbRayTrace

Features:
- Supports basic spheres, planes, cones, cylinder primitives
- Basic phong lighting
- Geometric transformations using translation, rotation and scaling matrices
- Moveable camera system
- Material support
- Refections
- Refractions
- UV Texture mapping (importing images and custom textures; voronoi, polka dots, checkerboard, plain, stripes)
- Noise generation; perlin, simplex (as textures)
- Post processing effects and filters

Example images
-

Post processing filters (Vignette, Gaussian Blur, Pixelisation):
![filters](https://user-images.githubusercontent.com/53636492/153784921-9a8533d0-4e5e-4343-bebb-6886fe4987f3.png)

Shadertoy-style noise textures and pattern textures:
![noise tex3](https://user-images.githubusercontent.com/53636492/153319639-bf3c1f4a-aa51-4ea1-93f5-c6218c58e594.PNG)

Displaying image textures:
![final tex render](https://user-images.githubusercontent.com/53636492/151657150-7bfe58f1-4834-4763-9d07-3f7612fa3060.PNG)

Cornell Box with shapes and patterns (has shadow acne issues):
![final cornell box](https://user-images.githubusercontent.com/53636492/150660611-30e6c056-427b-4da4-a524-93d31a9c85c7.PNG)

Cornell Box (has shadow depth issues):
![reflections-export](https://user-images.githubusercontent.com/53636492/149031954-15a2ffe1-8df9-4b7c-81b8-c6cba5974f8e.png)
