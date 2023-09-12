#include "Button.h"

//Initialize member variables
Button::Button()
{
    mInside = false;
    mPressed = false;
    mUnpressed = false;
    mFullClicked = false;

    mPosX = 0;
    mPosY = 0;
    
    mRenderRect = new SDL_Rect;
}

void Button::handleEvents(SDL_Event &e)
{
    //Check if there is any mouse event (that we can handle)
    if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEMOTION){

        //Get the mouse x and y position on the board
        int mouseX, mouseY;
        int buttonX = mPosX;
        int buttonY = mPosY;

        Window::getInstance()->getScaledMousePosition(&mouseX, &mouseY);

        //Set inside to true, set to false if outside texture boundaries
        mInside = true;
        if(mouseX < buttonX){
            mInside = false;
        }
        else if(mouseX > buttonX + mWidth){
            mInside = false;
        }
        else if(mouseY < buttonY){
            mInside = false;
        }
        else if(mouseY > buttonY + mHeight){
            mInside = false;
        }

        //If mouse is inside, set correct booleans
        if(mInside){
            switch(e.type){
                case SDL_MOUSEBUTTONDOWN:
                mPressed = true;
                mUnpressed = false;
                break;

                case SDL_MOUSEBUTTONUP:
                mUnpressed = true;
                if(mPressed){
                    mFullClicked = true;
                }
                mPressed = false;
                break;
            }
        }
        //If mouse is not inside, set correct booleans better
        else if(e.type == SDL_MOUSEBUTTONUP){
            mUnpressed = true;
            mPressed = false;
        }
    }
}


void Button::render(int x, int y)
{
    //If mouse is inside, darken the color by 1/2
    if(mInside){
        mButtonTexture.setColor(128, 128, 128);
        //If mouse button is pressed, darken color by 3/4
        if(mPressed){
            mButtonTexture.setColor(64, 64, 64);
        }
    }
    //Otherwise set color as normal
    else{
        mButtonTexture.setColor(255, 255, 255);
    }

    mPosX = x;
    mPosY = y;
    mButtonTexture.render(mPosX, mPosY, 1.0, mRenderRect);
}

void Button::loadTexture(const std::string &path, SDL_Rect *renderRect)
{
    if(!mButtonTexture.loadFromFile(path.c_str())){
        std::cout << "Error loading button texture from path: " << path << std::endl;
    }

    mWidth = mButtonTexture.getWidth();
    mHeight = mButtonTexture.getHeight();

    //Set dimensions based on input renderRect if defined
    if(renderRect){
        mRenderRect->w = renderRect->w;
        mRenderRect->h = renderRect->h;
        mRenderRect->x = renderRect->x;
        mRenderRect->y = renderRect->y;

        mWidth = mRenderRect->w;
        mHeight = mRenderRect->h;
    }
    else{
        mRenderRect = nullptr;
    }

    //Set the texture to blend with the background (as a png should)
    mButtonTexture.setBlending(SDL_BlendMode::SDL_BLENDMODE_BLEND);
}

bool Button::isInside()
{
    return mInside;
}

bool Button::isPressed()
{
    return mPressed;
}

bool Button::isUnpressed()
{
    return mUnpressed;
}

bool Button::clicked()
{
    //If we query asking the button if it is clicked,
    //set to false so we can query again
    if(mFullClicked){
        mFullClicked = false;
        mInside = false;
        return true;
    }

    return false;
}

int Button::getWidth()
{
    return mWidth;
}

int Button::getHeight()
{
    return mHeight;
}

Button::~Button()
{
    delete mRenderRect;
    mRenderRect = nullptr;
    mButtonTexture.free();
}
