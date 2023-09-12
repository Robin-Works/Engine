#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"
#include <iostream>

class Timer
{
public:

    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    uint32_t getTicks();

    bool isStarted();
    bool isPaused();

private:

    uint32_t mStartTicks;
    uint32_t mPausedTicks;

    bool mPaused;
    bool mStarted;
};

#endif