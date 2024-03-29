//
//  timer.cpp
//  serialtest
//
//  Created by Michael Hill on 4/9/16.
//  Copyright © 2016 Michael Hill. All rights reserved.
//

#include "timer.h"
#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace Tools;

class TimerImpl : public Timer
{
public:
    TimerImpl() {};
    void start()
    {
        startTime = high_resolution_clock::now();
    }
    
    double getTime()
    {
        std::chrono::high_resolution_clock::time_point now = high_resolution_clock::now();
        duration<double> dur = duration_cast<duration<double> >(now - startTime);
        return dur.count();
    }
    
private:
    high_resolution_clock::time_point startTime;
};

Timer* Timer::createTimer()
{
    return new TimerImpl();
}

Timer* _singletonTimer = NULL;

void Timer::startProgramTimer()
{
    if (_singletonTimer == NULL)
    {
        _singletonTimer = createTimer();
    }
    _singletonTimer->start();
}

unsigned int Timer::millis()
{
    return _singletonTimer->getTime() * 1000.0;
}

unsigned int Timer::micros()
{
    return _singletonTimer->getTime() * 1000000.0;
}