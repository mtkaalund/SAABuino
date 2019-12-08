#include <TimeInterrupt.h>
/*
This project is build on https://hackaday.io/project/158595/gallery#c95bac70f561ae865c572f3897c6257d
The idea is to add some more functionalty to our beloved SAABs.

As the original project have implmented blink 3 times, 
in this project there are going to be implemnted

* Follow Me Home Light
* Autointerval rear window


Arduino Libraries that are used in this projects:
https://github.com/matthew-dickson-epic/TimeInterrupt
*/
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
    break;

    case BLINK_LEFT:
    break;
  }

  delay(200); // This is code is run every 200 ms
}

void autointerval_rearwiper() {
  pinMode(DICE_PIN_19, OUTPUT);
  digitalWrite(DICE_PIN_19, LOW);
  delay(2);
  digitalWrite(DICE_PIN_19, HIGH);
}
