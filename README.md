# miniRT
RayTracing project

Graphics library used:
- miniLibx (https://github.com/42Paris/minilibx-linux)

To compile miniLibx:
- https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#installation

To compile miniRT:
- make

Program's OS Compatibility:
- Linux
- macOS

Example of input file:

![image](https://user-images.githubusercontent.com/71138634/214985403-1a4c82ee-61f4-4395-998e-fe3974fcbb95.png)

Ambient lightning:
- identifer: A
- ambient lighting ratio in range [0.0,1.0]: 0.2
- R,G,B colors in range [0-255]: 255, 255, 255

Camera:
- identifer: C
- x,y,z coordinates of the view point: 0.0,0.0,20.6
- 3d normalized orientation vector 0.0,0.0,1.0 In range [-1,1] for each x,y,z axis:
- FOV : Horizontal eld of view in degrees in range [0,180]

Light:
- identifer: L
- x,y,z coordinates of the light point: 0.0,0.0,20.6
- the light brightness ratio in range [0.0,1.0]: 0.6 (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255

Sphere:
- identifer: sp
- x,y,z coordinates of the sphere center: 0.0,0.0,20.6
- the sphere diameter: 12.6
- R,G,B colors in range [0-255]: 10, 0, 255

Plane:
- identifer: pl
- x,y,z coordinates: 0.0,0.0,-10.0
- 3d normalized orientation vector 0.0,0.0,1.0  In range [-1,1] for each x,y,z axis:
- R,G,B colors in range [0-255]: 0, 0, 255

Cylinder:
- identifer: cy
- x,y,z coordinates: 50.0,0.0,20.6
- 3d normalized orientation vector  0.0,0.0,1.0  In range [-1,1] for each x,y,z axis:
- the cylinder diameter: 14.2
- the cylinder height: 21.42
- R,G,B colors in range [0,255]: 10, 0, 255
