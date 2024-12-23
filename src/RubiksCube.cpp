#include "RubiksCube.hpp"
#include <cstdlib> // For random scrambling

RubiksCube::RubiksCube() : rotatingLayer(-1), rotationAxis(-1), rotationAngle(0), isClockwise(true) {
    reset(); // Initialize the cube in its solved state
}

void RubiksCube::reset() {
    cubelets.clear();
    for (float x = -1; x <= 1; ++x) {
        for (float y = -1; y <= 1; ++y) {
            for (float z = -1; z <= 1; ++z) {
                if (!(x == 0 && y == 0 && z == 0)) { // Skip the center cubelet
                    Cubelet cubelet(x, y, z);
                    if (x == 1) cubelet.setColor(5, 5); // Right face (Orange)
                    if (x == -1) cubelet.setColor(4, 4); // Left face (Red)
                    if (y == 1) cubelet.setColor(2, 2); // Top face (Green)
                    if (y == -1) cubelet.setColor(3, 3); // Bottom face (Blue)
                    if (z == 1) cubelet.setColor(0, 0); // Front face (White)
                    if (z == -1) cubelet.setColor(1, 1); // Back face (Yellow)
                    cubelets.push_back(cubelet);
                }
            }
        }
    }
}

void RubiksCube::draw() {
    glPushMatrix();

    // Apply rotation to the currently rotating layer
    if (rotatingLayer != -1) {
        glRotatef(rotationAngle, rotationAxis == 0, rotationAxis == 1, rotationAxis == 2);
    }

    for (size_t i = 0; i < cubelets.size(); ++i) {
            cubelets[i].draw(); // Access cubelet using indexed loop
    }

    glPopMatrix();
}

void RubiksCube::rotateLayer(int axis, int layer, bool clockwise) {
    rotatingLayer = layer;
    rotationAxis = axis;
    isClockwise = clockwise;
    rotationAngle = 0; // Start the rotation

    // Traditional for loop (for C++98 compatibility)
    for (size_t i = 0; i < cubelets.size(); ++i) {
        Cubelet& cubelet = cubelets[i];  // Explicitly refer to the cubelet
        // Check if the cubelet is on the correct layer
        if ((axis == 0 && cubelet.getX() == layer) ||
            (axis == 1 && cubelet.getY() == layer) ||
            (axis == 2 && cubelet.getZ() == layer)) {
            cubelet.rotate(axis, clockwise);
        }
    }
}

void RubiksCube::rotateAdjacentFaces(int axis, int layer, bool clockwise) {
    // This function rotates the adjacent colors for the layer's rotation.
    // We need to swap the adjacent colors on the top/bottom/left/right faces.

    // Define the four adjacent faces depending on the axis of rotation
    std::vector<int> adjacentFaces;

    if (axis == 0) { // X-axis (left/right rotation)
        adjacentFaces.push_back(2); // Top
        adjacentFaces.push_back(3); // Bottom
        adjacentFaces.push_back(1); // Front
        adjacentFaces.push_back(0); // Back (Clockwise order)
    } else if (axis == 1) { // Y-axis (up/down rotation)
        adjacentFaces.push_back(4); // Left
        adjacentFaces.push_back(5); // Right
        adjacentFaces.push_back(1); // Front
        adjacentFaces.push_back(2); // Back (Clockwise order)
    } else if (axis == 2) { // Z-axis (front/back rotation)
        adjacentFaces.push_back(4); // Left
        adjacentFaces.push_back(5); // Right
        adjacentFaces.push_back(0); // Top
        adjacentFaces.push_back(3); // Bottom (Clockwise order)
    }

    // Now, rotate the color arrays of the 4 adjacent faces in the correct direction
    if (clockwise) {
        // Swap the adjacent color arrays (clockwise direction)
        std::swap(cubelets[adjacentFaces[0]], cubelets[adjacentFaces[3]]);
        std::swap(cubelets[adjacentFaces[1]], cubelets[adjacentFaces[2]]);
    } else {
        // Swap the adjacent color arrays (counterclockwise direction)
        std::swap(cubelets[adjacentFaces[0]], cubelets[adjacentFaces[2]]);
        std::swap(cubelets[adjacentFaces[1]], cubelets[adjacentFaces[3]]);
    }
}




void RubiksCube::updateRotation() {
    if (rotatingLayer != -1) {
        rotationAngle += isClockwise ? 5.0f : -5.0f; // Rotate incrementally

        // Finish the rotation after 90 degrees
        if (rotationAngle >= 90 || rotationAngle <= -90) {
            rotationAngle = 0;
            rotatingLayer = -1;
        }
    }
}


void RubiksCube::scramble() {
    for (int i = 0; i < 20; ++i) {
        int axis = rand() % 3; // Random axis (0 = X, 1 = Y, 2 = Z)
        int layer = rand() % 3 - 1; // Random layer (-1, 0, 1)
        bool clockwise = rand() % 2; // Random direction
        rotateLayer(axis, layer, clockwise);
    }
}
