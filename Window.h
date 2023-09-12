#ifndef WINDOW_H
#define WINDOW_H

#include "Constants.h"
#include "Camera.h"
#include <iostream>

class Window
{
public:

    bool init();

    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();

    void handleEvent(SDL_Event &e);

    void free();

    static Window* getInstance();

    int getWidth();
    int getHeight();

    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();
    bool isShown();

    bool isFullscreen();

    bool mQuit;

    void getScaledMousePosition(int *mousePosX, int *mousePosY);

private:

    Window();
    ~Window();

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    int mWidth;
    int mHeight;
    int mWindowDisplayID;

    bool mMouseFocus;
    bool mKeyboardFocus;
    bool mFullscreen;
    bool mMinimized;
    bool mShown;

    static Window *mInstance;

};

#endif