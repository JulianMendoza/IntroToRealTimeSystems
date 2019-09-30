# IntroToRealTimeSystems

A collection of projects studying real-time systems.

## Managing Interrupts

<p align="center">
<img src="Lab3.gif" height="20%" width="20%">
 </p>

In this demo, we have two inputs and two outputs. 
* Switch one toggles between LEDS (default: red). 
* Switch two toggles between LED states (on/off or toggling through all RGB states).

## Managing Timers

<p align="center">
<img src="Lab4.gif" height="20%" width="20%">
 </p>

In this demo, we deal with a 16 bit timer. 
* Switch one toggles between LEDS
* Switch two toggles the timer
* Timer toggles LED states every one second (32.768kHz clock) CCR -> (0xFFFF-1)/2
