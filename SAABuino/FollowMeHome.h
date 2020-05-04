#ifndef FOLLOWMEHOME_H_
#define FOLLOWMEHOME_H_

#include "Function.h"
#include "DICE.h"

class FollowMeHome : public Function
{
private:
    bool RunConditions = false;

public:
    FollowMeHome()
    {
        run_time.ms = 500;
    }

    void update() override
    {
        // If the key is out and the drivers door is open
        if ((inputs.bits.key_is_out == 1) &&
            (inputs.bits.driver_door == 1))
            RunConditions = true;
    }

    void run() override
    {
        // When the key is out and the driver door is open. When DICE pin 41 is pulsed, 
        // the DICE should keep the lights on for 20 - 50 seconds as normal.
        // This can be reprogrammed with the TECH2 SAAB tool.
        if( RunConditions == true )
        {
            pinMode(DICE_PIN_41, OUTPUT);   // Setting DICE pin 41 to output
            digitalWrite(DICE_PIN_41, HIGH);// Setting DICE pin 41 to high
            delay(1);                       // Wait 1 ms
            digitalWrite(DICE_PIN_41, LOW); // Setting DICE pin 41 to low
            pinMode(DICE_PIN_41, INPUT);    // Returning it to input
        }
    }
};

#endif