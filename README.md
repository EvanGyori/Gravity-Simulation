# Gravity Simulation
A physics simulation where all circles are attracted to each other via gravitational force and perform elastic collisions.

## Controls
To create a new circle, hold left click on an empty spot and drag.

To move a circle around, hold left click on top of a circle and it will follow the cursor.

To apply velocity to a circle, hold right click on top of a circle and move mouse to determine magnitude. Let go to apply that amount of velocity in the applied direction.

Use WASD to pan view

Use mouse scroll wheel to zoom in and out.

## Usage
This program requires SFML 2. Make sure `SFMLConfig.cmake` can be found by CMake.

Create a build directory and run cmake from it
```
cmake <project-source-directory>
cmake --build .
```
Creates an executable called `Gravity`. Put the required SFML dll files with this executable in order to run it.
