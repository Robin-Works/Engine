#include "Statehandler.h"
#include "Menu.h"

StateHandler::StateHandler()
{
    //Set the first state to the menu
    mState = Menu::instance();
}

//Handles events for the current state
void StateHandler::handleEvents(SDL_Event& e)
{
    //The current state handles the events
    mState->handleEvents(this, e);
}

void StateHandler::doLogic()
{
    //The current state does the logic
    mState->doLogic(this);
}

void StateHandler::render()
{
    //The current state does the rendering
    mState->render(this);
}

//Calls exiting function on exiting state
void StateHandler::exitState(GameState* oldState)
{
    oldState->exitState();
}

//Sets the new state
void StateHandler::setState(GameState* newState)
{
    mState = newState;
}

//Calls the entering function for the new state
void StateHandler::enterState(GameState* newState)
{
    newState->enterState();
}
