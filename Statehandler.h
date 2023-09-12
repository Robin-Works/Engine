#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include "Gamestate.h"

//Class to handle state switching
class StateHandler
{
public:
    //Initializes to first state being used (menu)
    StateHandler();

    //Handles events of the current state
    void handleEvents(SDL_Event& e);

    //Does logic for the current state
    void doLogic();

    //Renders for the current state
    void render();

    //Sets the state to a new state
    void setState(GameState* newState);

    //Exiting function for exiting state
    void exitState(GameState* oldState);

    //Entering function for new state
    void enterState(GameState* newState);
private:

    //The current state handling events, logic, and rendering
    GameState* mState;
};

#endif