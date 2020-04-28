#ifndef TIMER_H_
#define TIMER_H_

// time holder
struct Timer
{
  uint16_t milisecond;
  uint8_t second;
  uint8_t minute;
  uint8_t hour;  
  
  Timer() {
    milisecond = 0;
    second = 0;
    minute = 0;
    hour = 0;  
  }
  
  void add_100ms()
  {
    milisecond += 100;
    if( milisecond >= 1000 )
    {
      milisecond -= 1000;
      second += 1;
      if(second >= 60)
      {
        second -= 60;
        minute += 1;
        if( minute >= 60 )
        {
          minute -= 60;
          hour += 1;
        }
      }
    }
  }
  
  void print_time()
  {
    Serial.print("ms: ");
    Serial.println(milisecond);
    Serial.print("s: ");
    Serial.println(second);
    Serial.print("m: ");
    Serial.println(minute);
    Serial.print("h: ");
    Serial.println(hour);
  }
};

Timer internal_timer;
#endif