
/*
 *  follow me home light
  virker ved at aktiverer langt lys imens fører døren er åben og nøglen er taget ud af tændingen, opgave, indgang på SAABuino,
  signal fra tændingslås nøgle ude, B+ ben 7 i DICE (TWICE ben 17) når fører døren åbnes kommer der + på ben 1 i DICE puls 
  udgang til DICE ben 41 tænder nærlys når døren lukkes igen program beskrivelse: B+ DICE ben 7 forsvinder når nøglen tages 
  ud & + fra DICE ben 1 ind på SAABuino i den rækkefølge skal give en puls ud til DICE ben 41
 */
#define DICE_PIN_1    // Driver door signal
#define DICE_PIN_7    // Key is out
#define DICE_PIN_19   // Rear window wiper
#define DICE_PIN_27   // Front window wiper
#define DICE_PIN_41   // Close light 

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
  }

  delay(200); // This is code is run every 200 ms
}
