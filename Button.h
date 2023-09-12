#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"
#include <string>

//A generic button class to handle simple button events
//Currently, only functionality for a user supplied texture
//TODO: Add a slider button? Add generic place-holder buttons
class Button
{
public:

    Button();

    //Renders the button at a specifc x and y position on the screen
    void render(int x, int y);

    //Handles button events
    void handleEvents(SDL_Event& e);

    //Loads the texture for the button
    void loadTexture(const std::string &path, SDL_Rect *renderRect = nullptr);

    //Returns if the mouse in inside the button
    bool isInside();
    
    //Returns if the button is currently pressed
    bool isPressed();

    //Returns if the button is not pressed
    bool isUnpressed();

    //Return if a full click (press and unpress on the button) has occurred
    bool clicked();

    //Returns button texture width
    int getWidth();

    //Returns button texture height
    int getHeight();

    ~Button();
private:

    //The texture and its width and height
    Texture mButtonTexture;
    int mWidth;
    int mHeight;

    //The button's position on the screen
    int mPosX;
    int mPosY;

    //Booleans to keep track of button state
    bool mInside;
    bool mPressed;
    bool mUnpressed;
    bool mFullClicked;

    //The render rect of the texture
    SDL_Rect *mRenderRect;
};

#endif