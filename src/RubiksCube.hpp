#ifndef RUBIKSCUBE_HPP
#define RUBIKSCUBE_HPP

#include "Cubelet.hpp"
#include <vector>
class RubiksCube {
public:
    RubiksCube();
    void reset();
    void draw();
    void rotateLayer(int axis, int layer, bool clockwise);
    void rotateAdjacentFaces(int axis, int layer, bool clockwise);
    void updateRotation();
    void scramble();

private:
    std::vector<Cubelet> cubelets;  // Make sure this is a vector of Cubelets
    int rotatingLayer;
    int rotationAxis;
    float rotationAngle;
    bool isClockwise;
};

#endif
