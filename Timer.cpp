#include "Timer.h"

//Initialize timer class
Timer::Timer()
{
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

//Start timer, get start ticks and set paused ticks to 0
void Timer::start()
{
    mStarted = true;

    mPaused = false;

    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

//Stop timer, set start and stop ticks to 0
void Timer::stop()
{
    mStarted = false;
    mPaused = false;

    mStartTicks = 0;
    mPausedTicks = 0;
}

//Pause time if started and not paused
//Paused ticks is getTicks - start ticks
//Set start ticks to 0
void Timer::pause()
{
    if(mStarted && !mPaused){
        mPaused = true;

        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

//Unpause timer if started and paused
//Start ticks is getTicks - paused ticks
//Set paused ticks to 0
void Timer::unpause()
{
    if(mStarted && mPaused){
        mPaused = false;

        mStartTicks = SDL_GetTicks() - mPausedTicks;

        mPausedTicks = 0;
    }
}

//Get timer ticks
uint32_t Timer::getTicks()
{
    uint32_t time = 0;

    if(mStarted){
        if(mPaused){
            time = mPausedTicks;
        }
        else{
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

//Return if timer is started
bool Timer::isStarted()
{
    return mStarted;
}

//Return if timer is paused
bool Timer::isPaused()
{
    return mPaused;
}