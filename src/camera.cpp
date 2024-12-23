#include "Camera.hpp"
#include <GL/glut.h>

Camera::Camera() : angleX(0), angleY(0), zoom(5), lastX(0), lastY(0) {}

void Camera::apply() {
    glTranslatef(0, 0, -zoom);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
}

void Camera::rotate(float deltaX, float deltaY) {
    angleX += deltaY;
    angleY += deltaX;
}

void Camera::zoomInOut(float deltaZoom) {
    zoom += deltaZoom;
    if (zoom < 3) zoom = 3;
    if (zoom > 15) zoom = 15;
}

void Camera::startDrag(int x, int y) {
    lastX = x;
    lastY = y;
}

void Camera::drag(int x, int y) {
    int deltaX = x - lastX;
    int deltaY = y - lastY;

    rotate(deltaX, deltaY);

    lastX = x;
    lastY = y;
}
