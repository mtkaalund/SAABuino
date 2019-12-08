
/*
This project is build on https://hackaday.io/project/158595/gallery#c95bac70f561ae865c572f3897c6257d
The idea is to add some more functionalty to our beloved SAABs.

As the original project have implmented blink 3 times, 
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

volatile states state, old_state;

void setup() {
  // put your setup code here, to run once:
  state = NONE;
  old_state = NONE;
  pinMode(DICE_PIN_1, INPUT);
  pinMode(DICE_PIN_7, INPUT);
}

void loop() {
  if( digitalRead(DICE_PIN_1) && !digitalRead(DICE_PIN_7) ) {
    // Change state to follow me home light
    old_state = state;
    state = FOLLOW_ME_HOME;
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
      pinMode(DICE_PIN_41, INPUT);
      state = old_state;
      old_state = NONE;
    break; 
    
    case AUTOINTERVAL_REARWINDOW:
    break;

    case BLINK_RIGHT:
    break;

    case BLINK_LEFT:
    break;
  }

  delay(200); // This is code is run every 200 ms
}
