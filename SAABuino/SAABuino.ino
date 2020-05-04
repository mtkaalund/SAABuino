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
#include "Function.h"
#include "FollowMeHome.h"
#include "AutoIntervalRearWiper.h"

bool led_on = false;
struct time_tm print_time;
struct time_tm read_input_timer;

// This is hold our functions
Function * func_ptr[2];

void setup()
{
    // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    ReadDICEInput();
    // Setting up our compare timers
    read_input_timer.ms = 200;
    print_time.s = 20;
    func_ptr[0] = new FollowMeHome();
    func_ptr[1] = new AutoIntervalRearWiper();
}

void loop()
{
    // put your main code here, to run repeatedly:
    UpdateTime();

    if(internal_timer == print_time)
    {
        internal_timer.print_time();
        print_input();  
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

    // Here we check all functions in func_ptr
    for( auto ptr : func_ptr )
    {
        if(internal_timer == ptr->run_time)
        {
            ptr->run();
        }
    }

    // Read inputs every 200 ms
    if (internal_timer.time.ms % read_input_timer.ms == 0)
    {
        // Reading inputs
        ReadDICEInput();

        for( auto ptr : func_ptr )
        {
            ptr->update();
        }
    }
}