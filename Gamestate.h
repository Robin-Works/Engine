#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Texture.h"
#include <iostream>

//Declaration of statehandler which will change the game states
class StateHandler;

//Abstract GameState class which defines the current state of the game
//i.e. Menu, Settings, Main Game, etc.
class GameState
{
public:

    //Abstract handle events function
    virtual void handleEvents(StateHandler* sHandler, SDL_Event& e) = 0;

    //Abstract doLogic function
    virtual void doLogic(StateHandler* sHandler) = 0;

    //Abstract render function
    virtual void render(StateHandler* sHandler) = 0;

    //Abstract exit state function which should handle cleanup when exiting a state
    virtual void exitState() = 0;

    //Abstract enter state function which should handle initializations when entering a state
    virtual void enterState() = 0;

    virtual ~GameState() {};
};

#endif