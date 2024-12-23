#Instructions to Run Program

Create an Eclipse Project

1. Open Eclipse and create a new C++ project: a) File > New > C++ Project. b) Select Empty Project and set the toolchain to GCC (if on Windows, choose MinGW).
2. Add your project files (main.cpp, Cubelet.cpp, Cubelet.hpp, RubiksCube.cpp, RubiksCube.hpp, Menu.cpp, Menu.hpp, Camera.cpp, Camera.hpp).

Access Project Properties:

1. Right-click on your project in Eclipse.
2. Select Properties.

Navigate to the Linker Settings:

1. Go to C/C++ Build > Settings in the left-hand menu.
2. Under MinGW C++ Linker, find the Libraries section.

Add Required Libraries:

1. Click Add in the Libraries (-l) section.
2. Add the following libraries one at a time: a) opengl32 (OpenGL library for Windows) b) glu32 (OpenGL Utility library) c) freeglut (FreeGLUT library)

Add the Library Search Path:

1. Below the Libraries section, there is a Library Search Path (-L) option.
2. Click Add and specify the folder containing the .lib files for FreeGLUT and OpenGL. For example: a) C:\MinGW\lib (or wherever FreeGLUT was installed).

Include Directories for Headers:

1. Go to C/C++ General > Paths and Symbols in the left-hand menu.
2. Under the Includes tab: a) Add the path to your OpenGL headers (C:\MinGW\include\GL).

Build and Run

1. Build the Project: a) Click Project > Build All. b) Resolve any errors (e.g., missing includes or typos).
2. Run the Application: a) Go to Run > Run As > Local C/C++ Application. b) The Rubik's Cube simulator window should appear.