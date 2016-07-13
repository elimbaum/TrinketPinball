# Trinket Pinball
### Trinket Pro Library for EWM Arduino camp
Eli Baum, 2016

This libary serves to simplify many of the common tasks that campers will use to control their pinball games. The intention is to allow users to learn useful concepts without getting bogged down with the technicalities of the Arduino system.

## Installation
Download this repository as a zip and rename the folder `ewm`. Then move that folder into your Arduino sketchbook's `libraries` folder. To use in a sketch, select the library from **Sketch** > **Include Library**.

## API
The pinball API includes functions for controlling the speaker, DC motor, servo motor, 7-segment displays, and internal EEPROM. Most campers should needn't stray too far from this functionality.

Most library components contain *public-facing functions*, intended for use by campers, as well as other advanced-use (but still technically public) functions.

`initPinball()` sets up all necessary peripherals. It should be called as the first line of `void setup()` in every sketch using the library.

--

### Servo
The servo library allows for 255-bit control of the servo motor with timings between 0.8 (position 0) and 2.2 ms (position 255).
#### Public Methods
`servoUp()` move the servo to the up position (0 by default).

`servoDown()` move the servo to the down position (127 by default).

#### Advanced Methods

`initServo()` set up servo control. Automatically called by `initPinball()`.

`initServo(int up, int down)` set up servo control, manually specifying up and down positions instead of using defaults.

`servoWrite(int pos)` move the servo to the specified location (0 - 255).
