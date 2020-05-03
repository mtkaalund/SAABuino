#ifndef TIMER_H_
#define TIMER_H_
/*
 * File: Timer.h
 * Description:
 * This file is a part of the SAABuino project
 * This project is currently developed by Casper Hein Ankersen and Michael Torp Kaalund
 * 
 * The project got it is idea from https://hackaday.io/project/158595/gallery#c95bac70f561ae865c572f3897c6257d
 * The idea is to add some more functionalty to our beloved SAABs.
 * 
 * As the original project have implmented blink 3 times, 
 * in this project there are going to be implemented
 * 
 * - Follow Me Home Light
 * - Autointerval rear window
 * - Blink 3 times for lane change
*/

// If Time between is not defined, then define it to be 100ms
#ifndef TIMEBETWEEN
#define TIMEBETWEEN 100
#endif

struct time_tm
{
    uint16_t ms;
    uint8_t s;
    uint8_t m;
    uint8_t h;

    bool operator ==(const time_tm &b) const 
    {
        bool b_return = false;
        if(b.ms != 0)
            b_return = (ms == b.ms);
        if(b.s != 0)
            b_return = (s == b.s);
        if(b.m != 0)
            b_return = (m == b.m);
        if(b.h != 0)
            b_return = (h == b.h);
        return b_return;
        // if( ms == b.ms && s == b.s && m == b.m && h == b.h )
        //     return true;
        // else 
        //     return false;
    }
    bool operator !=(const time_tm &b) const
    {
        bool b_return = false;
        if(b.ms != 0)
            b_return = (ms != b.ms);
        if(b.s != 0)
            b_return = (s != b.s);
        if(b.m != 0)
            b_return = (m != b.m);
        if(b.h != 0)
            b_return = (h != b.h);
        return b_return;
        // if( ms == b.ms && s == b.s && m == b.m && h == b.h )
        //     return false;
        // else 
        //     return true;
    }
};

// Time holder
struct Timer
{
    struct time_tm time;

    Timer()
    {
        time.ms = 0;
        time.s = 0;
        time.m = 0;
        time.h = 0;
    }

    void update()
    {
        time.ms += TIMEBETWEEN;
        if (time.ms >= 1000)
        {
            time.ms -= 1000;
            time.s += 1;
            if (time.s >= 60)
            {
                time.s -= 60;
                time.m += 1;
                if (time.m >= 60)
                {
                    time.m -= 60;
                    time.h += 1;
                }
            }
        }
    }

    bool operator ==(const time_tm &b) const 
    {
        return time == b;
    }
    bool operator !=(const time_tm &b) const
    {
        return time != b;
    }

    void print_time()
    {
        Serial.print("ms: ");
        Serial.println(time.ms);
        Serial.print("s: ");
        Serial.println(time.s);
        Serial.print("m: ");
        Serial.println(time.m);
        Serial.print("h: ");
        Serial.println(time.h);
    }
};

Timer internal_timer;

// Our holding timer
unsigned long count_time;

void UpdateTime()
{
    if ((millis() - count_time) > TIMEBETWEEN)
    {
        internal_timer.update();
        count_time = millis();
    }
}

#endif