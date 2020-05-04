#ifndef DICE_H_
#define DICE_H_
/*
 * File: DICE.h
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
#include <avr/sleep.h>

void WakeSAAB();
void SleepSAAB();

/*      Pin on DICE   Arduino Pins */
#define DICE_PIN_20   5 // Blinker left side
#define DICE_PIN_44   3 // Blinker right side
#define DICE_PIN_1    4 // Driver door signal
#define DICE_PIN_7    2 // Key is out
#define DICE_PIN_19   6 // Rear window wiper
#define DICE_PIN_21   7 // Front window wiper
#define DICE_PIN_41   8 // Close light

// Bitfield hold for inputs
typedef union {
  uint8_t value;
  struct {
    int blink_left  : 1;
    int blink_right : 1;
    int driver_door : 1;
    int rear_wiper  : 1;
    int front_wiper : 1;
    int close_light : 1;
    int key_is_out  : 1;
    int reserved    : 1;
  } bits;
} dice_key;

dice_key inputs;

void ReadDICEInput()
{
  pinMode(DICE_PIN_20, INPUT); // Blinker left side
  if( digitalRead(DICE_PIN_20) )
  {
    inputs.bits.blink_left = 1;
  } else {
    inputs.bits.blink_left = 0;
  }
  pinMode(DICE_PIN_44, INPUT); // Blinker right side
  if( digitalRead(DICE_PIN_44) )
  {
    inputs.bits.blink_right = 1;
  } else {
    inputs.bits.blink_right = 0;
  }
  pinMode(DICE_PIN_1, INPUT); // Driver door signal
  if( digitalRead(DICE_PIN_1) )
  {
    inputs.bits.driver_door = 1;
  } else {
    inputs.bits.driver_door = 0;
  }

  pinMode(DICE_PIN_19, INPUT); // Rear window wiper
  if( digitalRead(DICE_PIN_19) )
  {
    inputs.bits.rear_wiper = 1;
  } else {
    inputs.bits.rear_wiper = 0;
  }

  pinMode(DICE_PIN_21, INPUT); // Front window wiper  
  if( digitalRead(DICE_PIN_21) )
  {
    inputs.bits.front_wiper = 1;
  } else {
    inputs.bits.front_wiper = 0;
  }
    
  pinMode(DICE_PIN_41, INPUT); // Close light
  if( digitalRead(DICE_PIN_41) )
  {
    inputs.bits.close_light = 1;
  } else {
    inputs.bits.close_light = 0;
  }
  
  pinMode(DICE_PIN_7, INPUT); // Key is out
  if( digitalRead(DICE_PIN_7) )
  {
    inputs.bits.key_is_out = 1;
  } else {
    inputs.bits.key_is_out = 0;
  }
}

// Here is our sleep and wake up functions.
void SleepSAAB()
{
  sleep_enable();                        // Enable sleep mode
  pinMode(DICE_PIN_7, INPUT);            // Setting DICE_PIN_7 to input
  attachInterrupt(0, WakeSAAB, HIGH);    // attachInterrupt an interrupt to DICE pin 7 or Arduino pin 2
  set_sleep_mode( SLEEP_MODE_PWR_DOWN ); // Full sleep
  digitalWrite(LED_BUILTIN, LOW);        // Turn off buildin led
  sleep_cpu();                           // Activate sleep mode.
  digitalWrite(LED_BUILTIN, HIGH);       // Turn on buildin led
}

void WakeSAAB()
{
  sleep_disable();                        // Disable sleep mode
  detachInterrupt(0);                     // remove interrupt from Arduino pin 2
}

#endif