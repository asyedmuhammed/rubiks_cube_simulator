#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
private:
    float angleX, angleY, zoom;
    int lastX, lastY; // Store the last mouse position for dragging

public:
    Camera();
    void apply();
    void rotate(float deltaX, float deltaY);
    void zoomInOut(float deltaZoom);
    void startDrag(int x, int y);
    void drag(int x, int y);
};

#endif
