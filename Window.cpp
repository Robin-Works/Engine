#include "Window.h"

//Single instance of window
Window *Window::mInstance = nullptr;

Window::Window()
{
    mWindow = nullptr;
    mRenderer = nullptr;
    mShown = false;
    mMinimized = false;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullscreen = false;
    mWidth = 0;
    mHeight = 0;

    mQuit = false;
}

Window::~Window()
{
    free();
}

//Access Window only through this function
Window *Window::getInstance()
{
    return mInstance ? mInstance : (mInstance = new Window);
}

//Initialize the window and renderer
//Returns true if successful
bool Window::init()
{
    //Create window
    //Position is undefined (center), with width and height from Constants.h
    //Flags say that window is visible and that window is resizable
    mWindow = SDL_CreateWindow("Generic Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    //Check if mWindow was actually created
    if(mWindow){
        //Set width, height, and mouseFocus+keyboardFocus
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;
        
        //Create the renderer
        //Takes the window that was created, uses required drivers, sets renderer to accelerated and VSYNC
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //Check if mRenderer was actually created
        if(!mRenderer){
            std::cout << "Renderer not created! Error: " << SDL_GetError() << std::endl;

            //shutt'r down if not made properly
            SDL_DestroyWindow(mWindow);
            mWindow = nullptr;
        }
        else{
            //Get window display ID if created, set shown to true
            mWindowDisplayID = SDL_GetWindowDisplayIndex(mWindow);

            //Set Renderer to scale to screen width and height
            SDL_RenderSetLogicalSize(mRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            //Set this for scaling, remove if not scaling shit anymore
            SDL_RenderSetLogicalSize(mRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            mShown = true;
        }
    }
    else{
        std::cout << "Error! Window not created. Error: " << SDL_GetError() << std::endl;
    }

    //returns true if both created properly
    return mWindow != nullptr && mRenderer != nullptr;
}

//Handles basic window events
void Window::handleEvent(SDL_Event &e)
{
    if(e.type == SDL_WINDOWEVENT){
        switch(e.window.event){
            //Check for display change if window moved
            case SDL_WINDOWEVENT_MOVED:
            mWindowDisplayID = SDL_GetWindowDisplayIndex(mWindow);
            break;

            //Check if window size was changed
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            mWidth = e.window.data1;
            mHeight = e.window.data2;

            //update camera here
            Camera::getCamera()->updateDimensions(mWidth, mHeight);

            SDL_RenderPresent(mRenderer);
            break;

            //Check if window gets exposed
            case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(mRenderer);
            break;

            //Check if mouse entered/left the screen
            case SDL_WINDOWEVENT_ENTER:
            mMouseFocus = true;
            break;

            case SDL_WINDOWEVENT_LEAVE:
            mMouseFocus = false;
            break;

            //Check if a different application is in front of window
            case SDL_WINDOWEVENT_FOCUS_GAINED:
            mKeyboardFocus = true;
            break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
            mKeyboardFocus = false;
            break;

            //Check if window was minimized, maximized, or restored
            case SDL_WINDOWEVENT_MINIMIZED:
            mMinimized = true;
            break;

            case SDL_WINDOWEVENT_MAXIMIZED:
            mMinimized = false;
            break;

            case SDL_WINDOWEVENT_RESTORED:
            mMinimized = false;
            break;
        }
    }
    else if(e.type == SDL_KEYDOWN){
        //Maximize/minimize screen if pressed F1
        if(e.key.keysym.sym == SDLK_F1){
            if(mFullscreen){
                SDL_SetWindowFullscreen(mWindow, false);
                mFullscreen = false;
            }
            else{
                SDL_SetWindowSize(mWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
                if(SDL_SetWindowFullscreen(mWindow, true) == -1){
                    std::cout << "Error setting window fullscreen. Error: " << SDL_GetError() << std::endl;
                }

                mFullscreen = true;
                mMinimized = false;
            }
            //Put other keydown events here if needed
        }
    }
}

//Destroys window and renderer
//Called in destructor
void Window::free()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    mWindow = nullptr;
    mRenderer = nullptr;

    mShown = false;
    mMinimized = false;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullscreen = false;

    mWidth = 0;
    mHeight = 0;
}

//Access to the renderer
SDL_Renderer *Window::getRenderer()
{
    return mRenderer;
}

//Access to the window
SDL_Window *Window::getWindow()
{
    return mWindow;
}

//Return Window Height
int Window::getHeight()
{
    return mHeight;
}

//Return Window width
int Window::getWidth()
{
    return mWidth;
}

//Return if the window has mouse focus
bool Window::hasMouseFocus()
{
    return mMouseFocus;
}

//Return if the window has keyboard focus
bool Window::hasKeyboardFocus()
{
    return mKeyboardFocus;
}

//Return if the window is fullscreen
bool Window::isFullscreen()
{
    return mFullscreen;
}

//Return if the window is minimized
bool Window::isMinimized()
{
    return mMinimized;
}

//Return if the window is shown
bool Window::isShown()
{
    return mShown;
}

void Window::getScaledMousePosition(int *mousePosX, int *mousePosY)
{
    SDL_GetMouseState(mousePosX, mousePosY);
    double dMouseX, dMouseY;
    dMouseX = *mousePosX;
    dMouseY = *mousePosY;

    //Get window width and height for scaling
    int windowW, windowH;
    SDL_GetWindowSize(mWindow, &windowW, &windowH);
    
    //Scaling works properly for fullscreen so no offset needed
    if(!mFullscreen){
        //The render scale is window height divided by render height when window width to window height ratio is greater than 4/3
        //Essentially, this just is about the black spaces on the edges (left and right)
        if(static_cast<double>(windowW) / windowH > (4.0/3.0)){
            //Think of render scale like this: (New Render Dimensions / Old Render dimensions)
            //Everything is scaled based off this (texture sizes, mouse coords, rendering coords)
            double renderScale = static_cast<double>(windowH) / SCREEN_HEIGHT;

            //Mouse X position is the originial position, minus the black space on the left, divided by the scale
            //Puts double mouse X as if it were in the original 640 x 480 screen
            dMouseX = (*mousePosX - ((windowW - (SCREEN_WIDTH*renderScale)) / 2)) / renderScale;
            //MouseY is just scaled normally (no black spaces)
            dMouseY = *mousePosY / renderScale;
        }//Otherwise render scale is the opposite, esseintally defining black spaces above and below
        else if(static_cast<double>(windowW) / windowH < (4.0/3.0)){
            double renderScale = static_cast<double>(windowW) / SCREEN_WIDTH;

            //MouseX is scaled normally (no black spaces)
            dMouseX = *mousePosX / renderScale;
            //Mouse Y position is the originial position, minus the black space above, divided by the scale
            //Puts double mouse Y as if it were in the original 640 x 480 screen
            dMouseY = (*mousePosY - ((windowH - (SCREEN_HEIGHT*renderScale)) / 2)) / renderScale;
        }

        *mousePosX = static_cast<int>(dMouseX);
        *mousePosY = static_cast<int>(dMouseY);
    }
}
