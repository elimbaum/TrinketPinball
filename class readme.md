# Trinket Pinball 2016

### Basics
**Uploading Code** Plug your Trinket into USB and press the reset button. You can only upload code if the red LED is pulsing.

**Program Template** Every program you write needs to have the following:

    #include <ewm.h>

    void setup() {
      initPinball();
    }

    void loop() {

    }

To include the library, select it from **Sketch** > **Include Library**.

### C Syntax
We write code for the Trinket in the C programming language. Here are some tips for writing C code.

**Semicolons [VERY IMPORTANT!]** C uses semicolons (`;`) to know where lines of code end. *Every line of code you write must have a semicolon at the end.* The only exception is lines ending with curly brackets (`{}`), which do not need semicolons.

**Comments** Lines beginning with two slashes `//` are a comment, and are ignored by the Trinket. Use comments

**Variables** We can store information in *variables.* This is useful if you use one value many times throughout your program (like a delay time) or if you want to save values (like a score).

    // Declaration (at the top of your file)
    int foo = 0;

    // Elsewhere in your code
    foo = millis();
    digitalWrite(foo, LOW);

You can use the following *datatypes*:
  + `boolean` true/false or on/off values
  + `byte` very small numbers (0 to 255). Used for 7-segment programming.
  + `int` medium sized numbers (±32767). Most common.
  + `long` very big values (±2147483647). Used for timing.

**Functions** Functions are little chunks of code packaged into a single line. Run them by writing their name followed by parentheses:

    function();

Some functions take extra information in the form of arguments:

    function(argument1, argument2, argument3);

Some functions return a value into a variable:

    foo = function(argument1, argument2);


**Conditionals**

**Loops**

**Boolean Operators**

### Library Code


### Going Home
If you would like to work on your pinball machine at home, you'll need to install the Arduino software. Follow the "Super Easy Instructions" at this link:

https://learn.adafruit.com/adafruit-arduino-ide-setup/arduino-1-dot-6-x-ide
