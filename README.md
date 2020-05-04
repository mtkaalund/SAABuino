# The SAABuino project

 The project got it is start from https://hackaday.io/project/158595-3-blink-modification-for-saab-9-5 where the user saabman has hacked in a
 arduino into the SAAB's DICE module.
 As we were looking into the project, we realisted that we could implement more
 functionality to our (old) SAAB's.

 We will keep the original author's lane change (blink 3 times), but there will be a rewrite of it.

## Functionality implemented
When some of the functionality is implemented, the description of how it works should be here.

### Autointerval rear wiper
I had a problem, when driving in the rain my rear window would be needing to be wiped ever so offen.
So if the front wiper is activated, then when the rear wiper is activated. A timestamp is saved, then deactivate the rear wiper. When you need to wipe the rear window again, then activate it again, run for a full cycle and deactivate it again. This will set the timer for it to activated, so for as long the front wiper is on, then it will activate the rear wiper.

### Follow me home
This is a function that should already be in your SAAB. So take your key out and open the drivers door.
It will activate the head lights and the DICE should keep the lights on for 20 - 50 seconds (This is reprogrammable with the TECH2 SAAB tool).

## What to implement
- [x] Timer based function code
- [x] Follow me home light ( The DICE module should have the functionality )
- [ ] Lane change ( Blink 3 times ) left and right
- [x] Autointerval rear wiper ( either as a fixed interval or as a set time from driver )
- [ ] Sleeping when the key is out, and wake up when the key is inserted

## Hardware
* Arduino, any could be used but we have choosen to use a Arduino Pro Micro.
* DICE from a SAAB 9-5, 9-3 this module should be compatiable.

Following pins needed to be connected from the DICE module to the arduino.

DICE pins   | Arduino pins  | Description
------------|---------------|-------------------
1           |  4            | Driver door signal
7           |  2            | Key is out
19          |  6            | Rear window wiper
20          |  5            | Blinker left side
21          |  7            | Front window wiper
41          |  8            | Main / Dipped beam
44          |  3            | Blinker right side

This project is currently developed by Casper Hein Ankersen and Michael Torp Kaalund