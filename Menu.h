#ifndef MENU_H
#define MENU_H

#include "Statehandler.h"

//Menu state class to inherit from GameState
class Menu : public GameState
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

    Menu();

    //Singular instance of Menu state
    static Menu* mInstance;

    //Just a flag to know if
    bool enterMain;
};

#endif