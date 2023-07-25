# Physics Engine

This is a 2D physics engine written in C++.

Primitive supported: Point, line, AABB (Axis Aligned Bounding Box), OBB (Oriented Bounding Box), Circle

As of now

:white_check_mark: It has :
- Primitive shape motion simulation
- Primitive shape vs primitive shape collision detection
- [Impulse Solver](https://research.ncl.ac.uk/game/mastersdegree/gametechnologies/physicstutorials/5collisionresponse/Physics%20-%20Collision%20Response.pdf)

:memo: TODO :
- Move to smart pointers
- Angular velocity with shapes
- Collision resolution of boxes
- Broad phase collision detection (Quad tree)
- Logging and unit testing

## Getting started

1. Open Solution in [Microsoft Visual Studio](https://visualstudio.microsoft.com/downloads/)
2. Download [SFML](https://www.sfml-dev.org/download/sfml/2.6.0/) for the Demo project to work

Debug mode links libraries dynamiclly so copy the required SFML dlls in the ./bin/Win32/Debug
Release mode links library staticlly.

## Dependencies

The physics engine doesn't have any dependencies.
The demo project requires SFML.
