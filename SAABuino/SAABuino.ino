/*
 * SAABuino version 0.2
 * This project is currently developed by Casper Hein Ankersen and Michael Torp Kaalund
 * 
 * The project got it is idea from https://hackaday.io/project/158595/gallery#c95bac70f561ae865c572f3897c6257d
 * The idea is to add some more functionalty to our beloved SAABs.
 * 
 * As the original project have implmented blink 3 times, 
 * in this project there are going TO be implemented
 * 
 * - Follow Me Home Light
 * - Autointerval rear window
 * - Blink 3 times for lane change
*/
#define TIMEBETWEEN 50
#include "Timer.h"
#include "DICE.h"

bool led_on = false;

void setup()
{
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    ReadDICEInput();
}

void loop()
{
    // put your main code here, to run repeatedly:
    UpdateTime();

    if(internal_timer.second % 20 == 0 )
    {
        internal_timer.print_time();
        print_input();      
    }

    // Read inputs every 200 ms
    if (internal_timer.milisecond % 200 == 0)
    {
        // Reading inputs
        ReadDICEInput();
        if (led_on)
        {
            digitalWrite(LED_BUILTIN, LOW);
            led_on = false;
        }
        else
        {
            digitalWrite(LED_BUILTIN, HIGH);
            led_on = true;
        }
    }
}