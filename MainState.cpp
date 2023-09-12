#include "MainState.h"
#include "Menu.h"

MainState* MainState::mInstance = nullptr;

MainState::MainState()
{
    //Init textures or whatnot
    switchStateMenu = false;
}

//Return the instance of the mainstate
GameState* MainState::instance()
{
    return mInstance ? mInstance : (mInstance = new MainState);
}

void MainState::handleEvents(StateHandler* sHandler, SDL_Event& e)
{
    //Handle whatever events need to be handled
    if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_m){
            switchStateMenu = true;
        }
    }
}

void MainState::doLogic(StateHandler* sHandler)
{
    //Do whatever logic needs to be done
    if(switchStateMenu){
        sHandler->exitState(MainState::instance());
        sHandler->setState(Menu::instance());
        sHandler->enterState(Menu::instance());
    }
}

void MainState::render(StateHandler* sHandler)
{
    SDL_ShowCursor(1); //Set cursor to shown, not necessarily needed

    //Not needed, just to show state is working
    SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), 234, 162, 33, 255);
    SDL_Rect renderQuad = {0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight()};

    SDL_RenderFillRect(Window::getInstance()->getRenderer(), &renderQuad);
}

void MainState::exitState()
{

}

//Create new instance if not already
//Otherwise do normal stuff
void MainState::enterState()
{
    if(!mInstance){
        mInstance = new MainState;
    }
    else{
        switchStateMenu = false;
    }
}

