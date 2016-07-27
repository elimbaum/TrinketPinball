# Trinket Pinball
### Trinket Pro Library for EWM Arduino camp
Eli Baum, 2016

This libary serves to simplify many of the common tasks that campers will use to control their pinball games. The intention is to allow users to learn useful concepts without getting bogged down with the technicalities of the Arduino system.

## Installation
Download this repository as a zip and rename the folder `ewm`. Then move that folder into your Arduino sketchbook's `libraries` folder. To use in a sketch, select the library from **Sketch** > **Include Library**.

## API
The pinball API includes functions for controlling the speaker, DC motor, servo motor, 7-segment displays, and internal EEPROM. Most campers shouldn't need to stray too far from this functionality.

Most library components contain *public-facing functions*, intended for use by campers, as well as other advanced-use (but still technically public) functions.

`void initPinball()` – set up all necessary peripherals. It must be called as the first line of `void setup()` in every sketch that uses the library.

--

### Servo
The servo library allows for 256-position control of the servo motor with timings between 0.8 (position 0) and 2.2 ms (position 255).

#### Standard Methods
`void servoUp()` – move the servo to the up position (100 by default).

`void servoDown()` – move the servo to the down position (200 by default).

#### Advanced Methods

`void initServo(byte up, byte down)` – override up and down positions of the servo instead of using defaults.

`void setServo(byte pos)` – move the servo to the specified location (0 - 255).

### 7-segment Display
Three 7-segment displays, loaded via shift registers, allow users to display numbers and other characters on their pinball machine.

#### Standard Methods
`void displayNumber(int n)` – display a number (with leading zeros). Numbers that can't fit on the display will be replaced with either "bIg" or "neg".

`void clearDisplay()` – clear the display.

#### Advanced Methods
`void displayBytes(byte a, byte b, byte c)` – display the three bytes given. With standard clockwise digit arrangement, byte form is `A B C D E F G dp`. See `const byte numbers[]` for example bytes.

`const byte numbers[]` – an array containing 7-segment display bytes for the digits 0 through 9.

### Speaker
Inaudible PWM allows for 256-position control of the speaker. The speaker should not be run at full volume under normal conditions. Sustained full-volume usage may result in damage to the speaker, PCB, and nearby eardrums.

#### Standard Methods
`void tone(int freq)` – play a square wave tone at the specified frequency.

`void setSpeakerVolume(byte volPercent)` – set the volume as a percent. The default volume is 50.

`void speakerOff()` – turn off the speaker.

#### Advanced Methods
`void setSpeaker(byte value)` – manually sets the PWM value of the speaker. Used for PCM audio.

### EEPROM
The library uses EEPROM to store the high score and game count. By default, these addresses are arbitrarily assigned to locations 1000 and 1010, respectively. Advanced users are welcome to the use the EEPROM library themselves at their own discretion.

#### Standard Methods
`void updateHighScore(int score)` – set the high score to `score`.

`int readHighScore()` – get the high score from EEPROM.

`void clearHighScore()` – set the high score to zero.

`void updateGameCount()` – increment the game count by 1.

`int readGameCount()` – get the game count from EEPROM.

`void clearGameCount()` – set the game count to zero.

### Motor
PWM allows for 256-speed control of the DC motor. It should not be driven at full speed under normal conditions. Doing so may result in greatly reduced motor life.

#### Standard Methods
`void setMotorSpeed(int speedPercent)` – set the motor speed as a percent. Note that this function scales output according to the constant `MAX_SPEED`, i.e. `motorSpeed(100)` sets the motor speed to `MAX_SPEED`.

#### Advanced Methods
`void setMotorSpeedPWM(byte speed)` – set the motor speed directly. This function ignores `MAX_SPEED`.

### Timing
The built-in Arduino timing functions use Timer0. However, the Backglass PCB uses Timer0 to drive the speaker and motor. Therefore, this library includes a rewrite of all timing functionality to use Timer2. Functionality is identical as long as all code uses the rewritten timing functions.
