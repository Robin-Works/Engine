#include "Menu.h"
#include "MainState.h"

Menu* Menu::mInstance = nullptr;

Menu::Menu()
{
    enterMain = false;
}

//Returns the instance of the Menu state
GameState* Menu::instance()
{
    return mInstance ? mInstance : (mInstance = new Menu);
}

//Handles events in the Menu state
void Menu::handleEvents(StateHandler* sHandler, SDL_Event& e)
{
    //Handle events here
    if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_SPACE){
            enterMain = true;
        }
    }
}

//Does logic for menu state
//Handles exiting, setting, and entering new state
void Menu::doLogic(StateHandler* sHandler)
{
    //Any logic for exiting, setting, and entering state here
    if(enterMain){
        sHandler->exitState(Menu::instance());
        sHandler->setState(MainState::instance());
        sHandler->enterState(MainState::instance());
    }
}

//Handles rendering of anything in the Menu
void Menu::render(StateHandler* sHandler)
{
    SDL_ShowCursor(1); //Set cursor to shown, not necessarily needed

    //Not needed, just to show state is working
    SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), 0, 128, 128, 255);
    SDL_Rect renderQuad = {0, 0, Window::getInstance()->getWidth(), Window::getInstance()->getHeight()};

    SDL_RenderFillRect(Window::getInstance()->getRenderer(), &renderQuad);
}

//Delete anything needed
void Menu::exitState()
{

}

//Can be used if needed when entering menu
void Menu::enterState()
{
    enterMain = false;
}