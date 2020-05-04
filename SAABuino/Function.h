#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "Timer.h"
#include "DICE.h"

class Function
{
public:
    struct time_tm run_time;
    Function()
    {
        run_time.ms = 0;
        run_time.s = 0;
        run_time.m = 0;
        run_time.h = 0;
    }

    virtual void update();
    virtual void run();
};

class TestFunc : public Function
{
public:
    TestFunc()
    {
        run_time.s = 10;
    }

    void run() override
    {
        Serial.println("This should be run every 10s");
    }
};

#endif