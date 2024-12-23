#include "Cubelet.hpp"
#include <GL/glut.h>
#include <iostream>

// Constructor to initialize a cubelet with a given position (x, y, z)
Cubelet::Cubelet(float x, float y, float z) : x(x), y(y), z(z) {
    // Initialize the colors array manually
    colors[0] = 0; // Front
    colors[1] = 1; // Back
    colors[2] = 2; // Top
    colors[3] = 3; // Bottom
    colors[4] = 4; // Left
    colors[5] = 5; // Right
}
// Set the color for a specific face (0 = front, 1 = back, etc.)
void Cubelet::setColor(int face, int color) {
    if (face >= 0 && face < 6) colors[face] = color;
}

// Draw the cubelet using OpenGL, colored based on its current face colors
void Cubelet::draw() {
    glPushMatrix();
    glTranslatef(x, y, z); // Position cubelet at (x, y, z)

    float halfSize = 0.45f; // Half size of a cubelet

    for (int face = 0; face < 6; ++face) {
        if (colors[face] == -1) continue; // Skip faces with no color assigned

        // Set the color based on face index
        switch (colors[face]) {
            case 0: glColor3f(1, 1, 1); break; // White
            case 1: glColor3f(1, 1, 0); break; // Yellow
            case 2: glColor3f(0, 1, 0); break; // Green
            case 3: glColor3f(0, 0, 1); break; // Blue
            case 4: glColor3f(1, 0, 0); break; // Red
            case 5: glColor3f(1, 0.5, 0); break; // Orange
        }

        glBegin(GL_QUADS);
        // Define the vertices for each face
        switch (face) {
            case 0: // Front face
                glVertex3f(-halfSize, -halfSize, halfSize);
                glVertex3f(halfSize, -halfSize, halfSize);
                glVertex3f(halfSize, halfSize, halfSize);
                glVertex3f(-halfSize, halfSize, halfSize);
                break;
            case 1: // Back face
                glVertex3f(-halfSize, -halfSize, -halfSize);
                glVertex3f(halfSize, -halfSize, -halfSize);
                glVertex3f(halfSize, halfSize, -halfSize);
                glVertex3f(-halfSize, halfSize, -halfSize);
                break;
            case 2: // Top face
                glVertex3f(-halfSize, halfSize, halfSize);
                glVertex3f(halfSize, halfSize, halfSize);
                glVertex3f(halfSize, halfSize, -halfSize);
                glVertex3f(-halfSize, halfSize, -halfSize);
                break;
            case 3: // Bottom face
                glVertex3f(-halfSize, -halfSize, halfSize);
                glVertex3f(halfSize, -halfSize, halfSize);
                glVertex3f(halfSize, -halfSize, -halfSize);
                glVertex3f(-halfSize, -halfSize, -halfSize);
                break;
            case 4: // Left face
                glVertex3f(-halfSize, -halfSize, halfSize);
                glVertex3f(-halfSize, halfSize, halfSize);
                glVertex3f(-halfSize, halfSize, -halfSize);
                glVertex3f(-halfSize, -halfSize, -halfSize);
                break;
            case 5: // Right face
                glVertex3f(halfSize, -halfSize, halfSize);
                glVertex3f(halfSize, halfSize, halfSize);
                glVertex3f(halfSize, halfSize, -halfSize);
                glVertex3f(halfSize, -halfSize, -halfSize);
                break;
        }
        glEnd();
    }

    glPopMatrix(); // Restore the previous transformation matrix
}

// Rotate the faces of the cubelet around the specified axis
void Cubelet::rotate(int axis, bool clockwise) {
    int temp;
    int temp2;
    // Rotate based on the axis (0 - X, 1 - Y, 2 - Z)
    if (axis == 0) {  // X-axis rotation (left-right rotation)
        if (clockwise) {
            // Rotate the front, back, top, bottom faces
            temp = colors[2]; // Top color
            temp2 = colors[3];
            colors[2] = colors[3]; // Bottom color
            colors[3] = colors[1]; // Back color
            colors[1] = colors[0]; // Front color
            colors[0] = temp;
        } else {
            // Rotate counterclockwise (reverse order)
            temp = colors[0]; // Front color
            colors[0] = colors[1]; // Back color
            colors[1] = colors[3]; // Bottom color
            colors[3] = colors[2]; // Top color
            colors[2] = temp;
        }
    } else if (axis == 1) {  // Y-axis rotation (up-down rotation)
        if (clockwise) {
            // Rotate the left, right, front, back faces
            temp = colors[4]; // Left color //saving color red
            temp2 = colors[5];
            colors[4] = colors[1]; // Right color //red to yellow
            colors[5] = colors[0]; // Front color //orange to yellow???
            colors[1] = temp2; // Back color //yellow to orange
            colors[0] = temp; //white to red
        } else {
            // Rotate counterclockwise (reverse order)
            temp = colors[0]; // Front color
            temp2 = colors[1];
            colors[0] = colors[1]; // Back color
            colors[1] = colors[5]; // Right color
            colors[5] = colors[4]; // Left color
            colors[4] = temp;
        }
    } else if (axis == 2) {  // Z-axis rotation (front-back rotation)
        if (clockwise) {
            // Rotate the top, bottom, left, right faces
            temp = colors[2]; // Top color
            colors[2] = colors[4]; // Left color
            colors[4] = colors[3]; // Bottom color
            colors[3] = colors[5]; // Right color
            colors[5] = temp;
        } else {
            // Rotate counterclockwise (reverse order)
            temp = colors[5]; // Right color
            colors[5] = colors[3]; // Bottom color
            colors[3] = colors[2]; // Top color
            colors[2] = colors[4]; // Left color
            colors[4] = temp;
        }
    }
}
