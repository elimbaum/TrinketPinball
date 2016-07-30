# Trinket Pinball 2016

<https://git.io/vKKZZ>

### Basics
**Uploading Code** Plug your Trinket into USB and press the reset button. You can only upload code if the red LED is pulsing.

**Program Template** Every program you write needs to have the following:

```c
#include <ewm.h>

void setup() {
  initPinball();
}

void loop() {

}
```

To include the library, select it from **Sketch** > **Include Library**.

### C Syntax
We write code for the Trinket in the C programming language. Here are some tips for writing C code.

**Semicolons [VERY IMPORTANT!]**
C uses semicolons (`;`) to know where lines of code end. *Every line of code you write must have a semicolon at the end.* The only exception is lines ending with curly brackets (`{}`), which do not need semicolons.

**Comments**
Lines beginning with two slashes (`//`) are a comment, and are ignored by the Trinket. Use comments to leave notes for your future self, or to explain sections of complicated code.

**Variables**
We can store information in *variables.* This is useful if you use one value many times throughout your program (like a delay time) or if you want to save values (like a score).

```c
// Declaration (at the top of your file)
int foo = 0;

// Elsewhere in your code
foo = millis();
digitalWrite(foo, LOW);
```

You can use the following *datatypes*:
  + `boolean` – *true* or *false*. May also be used as *HIGH* and *LOW*, or *1* and *0*.
  + `byte` – small, non-negative numbers (0 to 255), or eight individual *bits*. Used for advanced 7-segment programming.
  + `int` – medium sized numbers (-32767 to +32767). Most common.
  + `long` – large numbers (-2147483647 to +2147483647). Used for timing.
  + `float` – decimals like 0.5 or 17.625. All other numerical datatypes can only store whole numbers.

**Functions** are shortcuts to run chunks of code from a single line. Run them by writing their name followed by parentheses:

```c
function();
```
```c
doSomething();
```

Some functions take extra information in the form of *arguments*:

```c
function(argument1, argument2);
```
```c
blinkSeveralTimes(numberOfTimes);
```

Some functions *return* a value, which can be saved to a variable or treated as a number:

```c
foo = function(argument(s));
```
```c
startTime = getCurrentTime();
...
[other code]
...
timePassed = getCurrentTime() - startTime;
```

**Conditionals** allow you to run some code sometimes, and run other code other times.

Here's the format. Keep in mind that only one code block will run per conditional. So if the first condition is true, no other code will be run.

```c
if(condition1) {
    // This code runs if condition1 is true
}
else if(condition2) {
    // condition1 is false and condition2 is true
}
else if(condition3)
{
    // conditions 1 & 2 are false and condition3 is true
}
else {
    // all the conditions are false
}
```

You can have as many `else if`s as you want (or none). Writing an `else` is optional, but if you do use it, *it must be last*.

**Loops** come in two flavors. They allow you to run the same code many times over:

*For* loops are used for repeating code some number of times:

```c
// Count to 100
for(int i = 0; i <= 100; i++) {
    displayNumber(i);
}
```

*While* loops are used for repeating code until some other condition becomes true.

```c
while(score < 100) {
    // This code runs forever until score >= 100
}
// after the loop finishes, score >= 100
```

**Math** works just as it does outside of programming. Parentheses can be used to neaten things up.
- `a + b` addition
- `a - b` subtraction
- `a * b` multiplication
- `a / b` division
- `a % b` modulo (remainder from division)

**Boolean Operators** make up conditional statements, and allow us to create boolean expressions. Remember from the datatypes intro; these have one of two states: *true* or *false*. A boolean expression can be one of the following:

- a function that returns a boolean value, like `digitalRead(pin)`
- a number (0 is false, all other numbers are true)
- an (in)equality test:
    - `a == b` – is `a` equal to `b`?
    - `a != b` – is `a` not equal to `b`?
    - `a > b` – is `a` greater than `b`?
    - `a >= b` – is `a` greater than or equal to `b`?
    - `a < b` – is `a` less than `b`?
    - `a <= b` – is `a` less than or equal to `b`?
- a compound expression:
    - `a && b` (and) – are both `a` and `b` true?
    - `a || b` (or) – is at least one of `a` or `b` true?
    - `!a` (not) – is `a` false?

Just like in math, use parentheses to combine expressions.

### Arduino Code

Here are some Arduino functions you'll be using during the week.

`digitalWrite(LED, state)` controls digital pins – for us, that's just the LEDs. The `LED` argument can be:
- `BUMP_0_LED`
- `BUMP_1_LED`
- `BUMP_2_LED`

and the `state` argument can be `HIGH` (on) or `LOW` (off).

`digitalRead(sensor)` reads the current state of a sensor, and returns either `HIGH` or `LOW`.
- `BUMP_0_SENSE`, `BUMP_1_SENSE`, and `BUMP_2_SENSE` return `LOW` when they are pressed, and `HIGH` when they are not.
- `FLIP_L_SENSE` and `FLIP_R_SENSE` return `HIGH` when they are pressed, and `LOW` when they are not.
- `OUT_SENSE` and `RAMP_SENSE` return `LOW` when a marble is over them, and `HIGH` if not.

`millis()` returns the number of milliseconds since your program started running. There are 1000 milliseconds in one second.

`micros()` returns the number of microseconds since your program started running. There are 1000 microseconds in one millisecond, so there are 1,000,000 microseconds in one second.

`delay(time)` waits for a certain amount of time, given in milliseconds. All other code stops while your program is waiting. For example, `delay(1000);` waits for one second.

`delayMicroseconds(time)` waits for a certain amount of time, given in microseconds. This means that `delayMicroseconds(1000);` is the same as `delay(1);`.

`random(min, max)` returns a random integer between `min` (inclusive) and `max` (exclusive). So if you wanted a random number from 1 to 100, you would call `random(1, 101);`.


### Library Code

To make writing code in this camp easier, we've written some behind-the-scenes code (called a "library") that contains many functions to help you use your pinball machine. However, this code is specific to this project, so it won't work if you try to program something else.

`initPinball()` sets up a lot of behind-the-scenes code for the pinball machine. This function must be the first line of your `setup()` function.

#### Servo
`servoUp()` moves the servo to the up position.

`servoDown()` moves the servo to the down position.

#### 7-segment Display
`displayNumber(n)` displays a number.

`displayText("text", delay)` scrolls text at a specified speed.

`clearDisplay()` clears the display.

#### Speaker
`tone(frequency)` plays a tone at the specified frequency.

`dualTone(frequency1, frequency2)` plays two tones at the specified frequencies.

`setSpeakerVolume(percent)` sets the speaker volume (the default is 50 percent). Avoid using very high values to prevent damaging the speaker.

`speakerOff()` turns off the speaker.

#### Data Storage
`updateHighScore(score)` set the high score to `score`.

`readHighScore()` returns the high score.

`clearHighScore()` set the high score to zero.

`updateGameCount()` increments the game count by 1.

`readGameCount()` returns the game count.

`clearGameCount()` sets the game count to zero.

#### Motor
`setMotorSpeed(percent)` sets the motor speed (from 0 to 100 percent). Remember that using the motor can quickly drain the batteries.

### Going Home
If you would like to work on your pinball machine at home, you'll need to install the Arduino software. Follow the "Super Easy Instructions" at this link:

<https://learn.adafruit.com/adafruit-arduino-ide-setup/arduino-1-dot-6-x-ide>
