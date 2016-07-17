# Trinket Pinball
### Trinket Pro Library for EWM Arduino camp
Eli Baum, 2016

This libary serves to simplify many of the common tasks that campers will use to control their pinball games. The intention is to allow users to learn useful concepts without getting bogged down with the technicalities of the Arduino system.

## Installation
Download this repository as a zip and rename the folder `ewm`. Then move that folder into your Arduino sketchbook's `libraries` folder. To use in a sketch, select the library from **Sketch** > **Include Library**.

## API
The pinball API includes functions for controlling the speaker, DC motor, servo motor, 7-segment displays, and internal EEPROM. Most campers shouldn't need to stray too far from this functionality.

Most library components contain *public-facing functions*, intended for use by campers, as well as other advanced-use (but still technically public) functions.

`void initPinball()` sets up all necessary peripherals. It should be called as the first line of `void setup()` in every sketch using the library.

--

### Servo
The servo library allows for 255-bit control of the servo motor with timings between 0.8 (position 0) and 2.2 ms (position 255).

#### Standard Methods
`void servoUp()` move the servo to the up position (0 by default).

`void servoDown()` move the servo to the down position (127 by default).

#### Advanced Methods

`void initServo(int up, int down)` set up servo control, manually specifying up and down positions instead of using defaults. `initPinball()` provides default servo setup otherwise.

`void servoWrite(int pos)` move the servo to the specified location (0 - 255).

### 7-segment Display
Three 7-segment displays, controlled by 74HC164 shift registers, allow users to display numbers and other characters on their pinball machine.

#### Standard Methods
`void displayNumber(int n)` display a number on the displays. Leading zeros *are* displayed. Only the three least significant digits will be shown; 15627 displays as 627. Although this function runs very quickly, calling it in very quick succession may cause blurring to occur. Around 100 Hz update frequency works well, however.

`void clearDisplay()` clears the entire display.

#### Advanced Methods
`void displayBytes(byte a, byte b, byte c)` display the three bytes given on screen. With standard clockwise digit arrangement, byte form is `ABCDEFGdp`. Users can access `byte numbers[10]` which contains the default digits.

### Speaker
PWM-controlled speaker. The speaker is driven by a MOSFET off battery power and therefore should not be run at full volume, please.

#### Standard Methods
`void tone(int freq)` Play a square wave tone at the specified frequency.

`void speakerVolume(byte volPercent)` set the volume as a percent from 0 - 100%, where 100% is the maximum volume; by default the maximum is 127 (out of 255). The default volume is 64.

`void speakerOff()` turns off the speaker.

#### Advanced Methods
`void speaker(byte value)` manually sets the PWM value on the speaker. May be used for PWM audio

### EEPROM
The library uses EEPROM to store the high score and game count. By default, these addresses are arbitrarily assigned to locations 1000 and 1010, respectively. Advanced users are welcome to the use the EEPROM library themselves at their own discretion.

#### Standard Methods
`void updateHighScore(int score)` set the high score to `score`.

`int readHighScore()` returns the high score from EEPROM.

`void clearHighScore()` set the high score to zero.

`void updateGameCount()` increment the game count by 1.

`int readGameCount()` returns the game count from EEPROM.

`void clearGameCount()` sets the game count to zero.

### Motor
PWM-controllable DC motor. Like the speaker, the motor is driven off battery power so its speed should be limited.

#### Standard Methods
`void motorSpeed(int speedPercent)` set the motor speed as a percent, from 0 to 100%, where 100% is the defined constant `MAX_SPEED`; by default 127.

#### Advanced Methods
`void motorSpeedPWM(byte speed)` set the motor speed directly, via PWM. Be careful setting it to maximum speed (255).

### Timing
The built-in Arduino timing functions use Timer0. However, we made the mistake of attaching our motor and speaker to the timer0 hardware PWM pins. Therefore, the library includes a rewrite of all timing functionality to use Timer2, thus allowing us to use Timer0 for pure hardware PWM.


