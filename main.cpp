#include "Texture.h"
#include "Statehandler.h"

bool init();

bool loadMedia();

void close();

int main(int argc, char* argv[])
{
    if(!init()){
        std::cout << "Error initializing!" << std::endl;
    }
    else{
        if(!loadMedia()){
            std::cout << "Error loading media!" << std::endl;
        }
        else{
            Window::getInstance()->mQuit = false;
            SDL_Event e;

            //The Current Game State
            StateHandler gameState;

            while(!Window::getInstance()->mQuit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        Window::getInstance()->mQuit = true;
                    }
                    Window::getInstance()->handleEvent(e);
                    gameState.handleEvents(e);
                    //handle events
                }
                
                gameState.doLogic();
                //do logic

                SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), 0, 0, 0, 255);
                SDL_RenderClear(Window::getInstance()->getRenderer());

                //render anything else
                gameState.render();

                SDL_RenderPresent(Window::getInstance()->getRenderer());

            }
        }
    }

    close();
    
    return 0;
}

bool init()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1){
        std::cout << "Error initializing SDL systems!" << std::endl;
        success = false;
    }
    else{
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        if(!Window::getInstance()->init()){
            std::cout << "Error creating window and renderer!" << std::endl;
            success = false;
        }
        else{
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)){
                std::cout << "Error initializing IMG!" << std::endl;
                success = false;
            }
            
            if(TTF_Init() == -1){
                std::cout << "Error initializing TTF!" << std::endl;
                success = false;
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    //font stuff can go here

    return success;
}

void close()
{
    Window::getInstance()->free();
    //close font here

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}