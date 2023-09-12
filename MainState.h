#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "Statehandler.h"

//The state in which to have the gameplay
class MainState : public GameState
{
public:

    //Overriden handleEvents function
    virtual void handleEvents(StateHandler* sHandler, SDL_Event& e) override;

    //Overridden logic function
    virtual void doLogic(StateHandler* sHandler) override;

    //Overridden rendering function
    virtual void render(StateHandler* sHandler) override;

    //Overridden enter state function
    virtual void enterState() override;

    //Overridden exit state function
    virtual void exitState() override;

    //Access Menu state through this instance
    static GameState* instance();
private:

    MainState();

    //Singular instance of MainState
    static MainState* mInstance;

    bool switchStateMenu = false;
};

#endif