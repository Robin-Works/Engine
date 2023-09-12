#ifndef CAMERA_H
#define CAMERA_H

#include "SDL.h"

class Camera
{
public:

    static Camera *getCamera();

    void updatePosition(int x, int y);
    void updateDimensions(int w, int h);

    int x();
    int y();
    int w();
    int h();

private:

    static Camera *mInstance;
    SDL_Rect cameraRect;
    Camera();
};

#endif