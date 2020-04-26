#include <TimeInterrupt.h>
/*
This project is build on https://hackaday.io/project/158595/gallery#c95bac70f561ae865c572f3897c6257d
The idea is to add some more functionalty to our beloved SAABs.

As the original project have implmented blink 3 times, 
in this project there are going to be implemnted

* Follow Me Home Light
* Autointerval rear window
* Blink 3 times for lane change


Arduino Libraries that are used in this projects:
https://github.com/matthew-dickson-epic/TimeInterrupt
*/

/*      Pin on DICE   Arduino Pins */
#define DICE_PIN_20   2 // Blinker left side
#define DICE_PIN_44   3 // Blinker right side
#define DICE_PIN_1    4 // Driver door signal
#define DICE_PIN_7    5 // Key is out
#define DICE_PIN_19   6 // Rear window wiper
#define DICE_PIN_27   7 // Front window wiper
#define DICE_PIN_41   8 // Close light 

typedef enum {
  FOLLOW_ME_HOME,
  AUTOINTERVAL_REARWINDOW,
  BLINK_RIGHT,
  BLINK_LEFT,
  NONE
} states;

bool has_autointerval_rearwindow = false;
uint16_t debounce_time  = 500; // 500 ms
uint16_t blinker_on_time = 1750; // 1750 ms
uint16_t blinker_time_start = 0;
uint16_t debounce = 0;
bool blinker_left_on = false;
bool blinker_right_on = false;

volatile states state, old_state;

void setup() {
  // put your setup code here, to run once:
  state = NONE;
  old_state = NONE;
  pinMode(DICE_PIN_1, INPUT);
  pinMode(DICE_PIN_7, INPUT);
  pinMode(DICE_PIN_27, INPUT);
}

void loop() {
  if( digitalRead(DICE_PIN_1) && !digitalRead(DICE_PIN_7) ) {
    // Change state to follow me home light
    old_state = state;
    state = FOLLOW_ME_HOME;
  }

  if( digitalRead(DICE_PIN_27) ) {
    // Front window wiper is on
    old_state = state;
    state = AUTOINTERVAL_REARWINDOW;
  }

  if( (! digitalRead(DICE_PIN_27) ) && ( has_autointerval_rearwindow == true) )
  {
    TimeInterrupt.end();
    has_autointerval_rearwindow = false;
  }

  // Here read blinker botton
  if( digitalRead(DICE_PIN_20) || digitalRead(DICE_PIN_44) )
  {
    delay(50);
    if( blinker_right_on == false && digitalRead(DICE_PIN_44) )
    {
      state = BLINK_RIGHT;
    } else if( blinker_left_on == false && digitalRead(DICE_PIN_20))
    {
      state = BLINK_LEFT;   
    }
  } else {
    blinker_right_on = false;
    blinker_left_on = false;
  }

  switch( state )
  {
    case FOLLOW_ME_HOME:  
    // When the key is out and the driver door is open. When DICE pin 41 is pulsed, the DICE should keep the lights on for 20 - 50 seconds as normal.
    // This can be reprogrammed with the TECH2 SAAB tool.
      pinMode(DICE_PIN_41, OUTPUT);
      digitalWrite(DICE_PIN_41, HIGH);
      delay(1); // Wait 1 ms before going low
      digitalWrite(DICE_PIN_41, LOW);
      delay(1);
      digitalWrite(DICE_PIN_41, HIGH);
      pinMode(DICE_PIN_41, INPUT);
      state = old_state;
      old_state = NONE;
    break; 
    
    case AUTOINTERVAL_REARWINDOW:
      has_autointerval_rearwindow = true;
      TimeInterrupt.begin(NORMAL);
      TimeInterrupt.addInterrupt(autointerval_rearwiper, 1000*6*5);
      state = old_state;
      old_state = NONE;
    break;

    case BLINK_RIGHT:
      if( ( millis() - debounce ) > debounce_time )
      {
        if(blinker_left_on) // check if right blinker is on
        {
          blinker_left_on = false;
          digitalWrite(DICE_PIN_44, LOW);
          pinMode(DICE_PIN_44, INPUT);
        } else { //
          blinker_right_on = true;
          pinMode(DICE_PIN_20, OUTPUT);
          digitalWrite(DICE_PIN_20, HIGH);
          blinker_time_start = millis();
        }

        debounce = millis();
      }
    break;

    case BLINK_LEFT:
      if( (millis() - debounce ) > debounce_time )
      {
        if(blinker_right_on)
        {
          blinker_right_on = false;
          digitalWrite(DICE_PIN_20, LOW);
          pinMode(DICE_PIN_20, INPUT);
        } else {
          blinker_left_on = true;
          pinMode(DICE_PIN_44, OUTPUT);
          digitalWrite(DICE_PIN_44, HIGH);
          blinker_time_start = millis();
        }
        debounce = millis();
      }
    break;
  }

  // Check if one of the blinkers is on
  if( blinker_right_on || blinker_left_on )
  {
    // Checks for the time
    if( millis() > ( blinker_time_start + blinker_on_time ) )
    {
      if( blinker_right_on )
      {
        blinker_right_on = false;
        digitalWrite(DICE_PIN_20, LOW);
        pinMode(DICE_PIN_20, INPUT);
        if( digitalRead(DICE_PIN_20) )
        {
          state = BLINK_RIGHT;
        } else {
          state = NONE;
        }
      } else if( blinker_left_on ) 
      {
        blinker_left_on = false;
        digitalWrite(DICE_PIN_44, LOW);
        pinMode(DICE_PIN_44, INPUT);
        if( digitalRead(DICE_PIN_44) )
        {
          state = BLINK_LEFT;  
        } else {
          state = NONE;
        }
      }
    }
  }

  delay(200); // This is code is run every 200 ms
}

void autointerval_rearwiper() {
  pinMode(DICE_PIN_19, OUTPUT);
  digitalWrite(DICE_PIN_19, LOW);
  delay(2);
  digitalWrite(DICE_PIN_19, HIGH);
}
