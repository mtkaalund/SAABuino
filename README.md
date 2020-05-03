# The SAABuino project

 The project got it is start from https://hackaday.io/project/158595-3-blink-modification-for-saab-9-5 where the user saabman has hacked in a
 arduino into the SAAB's DICE module.
 As we were looking into the project, we realisted that we could implement more
 functionality to our (old) SAAB's.

 We will keep the original author's lane change (blink 3 times), but there will be a rewrite of it.

## What to implement
- [ ] Follow me home light ( The DICE module should have the functionality )
- [ ] Lane change ( Blink 3 times ) left and right
- [ ] Autointerval rear window ( either as a fixed interval or as a set time from driver )

## Hardware
* Arduino, any could be used but we have choosen to use a Arduino Pro Micro.
* DICE from a SAAB 9-5, 9-3 this module should be compatiable.

Following pins needed to be connected from the DICE module to the arduino.

DICE pins   | Arduino pins  | Description
------------|---------------|-------------------
1           |  4            | Driver door signal
7           |  5            | Key is out
19          |  6            | Rear window wiper
20          |  2            | Blinker left side
21          |  7            | Front window wiper
41          |  8            | Main / Dipped beam
44          |  3            | Blinker right side

This project is currently developed by Casper Hein Ankersen and Michael Torp Kaalund