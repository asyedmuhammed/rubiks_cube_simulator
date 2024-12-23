#ifndef CUBELET_HPP
#define CUBELET_HPP

#include <GL/glut.h>
#include <vector>
class Cubelet {
public:
    Cubelet(float x, float y, float z);

    void setColor(int face, int color);
    void draw();
    void applyRotation(float angle, int axis);

    // Getter functions for x, y, and z
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    // Rotate cubelet faces based on axis and direction
    void rotate(int axis, bool clockwise);

private:
    float x, y, z;
    int colors[6];  // Front, back, top, bottom, left, right
};


#endif
