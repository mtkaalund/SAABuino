#ifndef AUTOINTERVALREARWIPER_H_
#define AUTOINTERVALREARWIPER_H_

#include "Function.h"
#include "Timer.h"
#include "DICE.h"

class AutoIntervalRearWiper : public Function
{
private:
    bool RunConditions = false;
    bool RearWiperOnFirstTime = false;
    bool RearWiperOff = false;

    struct timer_tm first_activated;

public:
    AutoIntervalRearWiper()
    {
        // In this function, this the run_time will be set by user
    }

    void reset()
    {
        RearWiperOnFirstTime = false;
        RearWiperOff = false;
        RunConditions = false;
    }

    void update() override
    {
        if (inputs.bits.key_is_out == 0)
        {
            // If the front wiper is on.
            if (inputs.bits.front_wiper == 1)
            {
                // If the rear wiper is on
                if (inputs.bits.rear_wiper == 1)
                {
                    // If this is the first time it has been activated
                    if (RearWiperOnFirstTime == false)
                    {
                        RearWiperOnFirstTime = true;
                        first_activated = internal_timer.time;
                    }
                    else
                    {
                        if (RearWiperOff == true)
                        {
                            // Setting the time
                            run_time = internal_timer.time - first_activated;
                            RunConditions = true;
                        }
                    }
                }
                else
                {
                    if (RearWiperOnFirstTime == true && RearWiperOff == false)
                    {
                        RearWiperOff = true;
                    }
                    else
                    {
                        // Reset
                        reset();
                    }
                }
            }
        } else {
            reset();
        }
    }

    void run() override
    {
        if (RunConditions == true)
        {
            pinMode(DICE_PIN_19, OUTPUT);
            digitalWrite(DICE_PIN_19, HIGH);
            delay(100);
            digitalWrite(DICE_PIN_19, LOW);
            pinMode(DICE_PIN_19, INPUT);
        }
    }
};

#endif