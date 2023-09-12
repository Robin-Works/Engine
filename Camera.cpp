#include "Camera.h"

//Single camera instance
Camera *Camera::mInstance = nullptr;

Camera *Camera::getCamera()
{
    return (mInstance ? mInstance : mInstance = new Camera);
}

Camera::Camera()
{
    cameraRect.x = 0;
    cameraRect.y = 0;
    cameraRect.w = 640;
    cameraRect.h = 480;
}

//Update x and y coords of camera rect
void Camera::updatePosition(int x, int y)
{
    cameraRect.x = x;
    cameraRect.y = y;
}

//update width and height of camera rect
void Camera::updateDimensions(int w, int h)
{
    cameraRect.w = w;
    cameraRect.h = h;
}

//return x pos of camera rect
int Camera::x()
{
    return cameraRect.x;
}

//return y pos of camera rect
int Camera::y()
{
    return cameraRect.y;
}

//return width of camera rect
int Camera::w()
{
    return cameraRect.w;
}

//return height of camera rect
int Camera::h()
{
    return cameraRect.h;
}