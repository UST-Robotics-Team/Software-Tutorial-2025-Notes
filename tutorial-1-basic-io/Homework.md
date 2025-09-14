# T1: Homework

Tutorial 1 Homework

There will be 2 tasks.

Before you start doing homework, You may find these defines in `lcd.h` useful:

```c
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

#define MAX_WIDTH 128
#define MAX_HEIGHT 160

#define CHAR_MAX_X_VERTICAL 16
#define CHAR_MAX_Y_VERTICAL 10

#define CHAR_MAX_X_HORIZONTAL 20
#define CHAR_MAX_Y_HORIZONTAL 8

#define CHAR_MAX_X 20  // max between CHAR_MAX_X_VERTICAL and CHAR_MAX_X_HORIZONTAL
#define CHAR_MAX_Y 10  // max between CHAR_MAX_Y_VERTICAL and CHAR_MAX_Y_HORIZONTAL
```

## Task 1: **Edge Triggering vs Level Triggering**

> Total: 8

Consider 2 uses for a single button: (choose BTN1 or BTN2)

#### **Part 1: Level Triggering**

- While the button is down, print `Hello, (Your name)` on TFT **(@1)**
- While it is not, flash the LED (at least one LED). **(@1)**
- Two actions should not happen simultaneously.
- Hints:
  - In this case every time the loop comes around, we are concerned with the **current state** (or level) of the buttons GPIO Pin
  - The implementation of the button reading here should be obvious and simple

![](https://i.imgur.com/qSrTmjr.gif)&#x20;

> Notice the green button and the green LED

#### **Part 2: Edge Triggering**

- We want to print `Hello, (Your name)` for 1 second when the button is pressed, but only once for each press, so holding the button does nothing more. **(@1)**
- When the button is released, we want to flash the LED for 1 second, but again only once for each release. **(@1)**
- The process repeats. i.e. it will print text again if you click the button. **(@1)**
- Keywords:
  - The event of a signal going from low to high is called the _**rising edge**_ and the opposite is the _**falling edge**_
  - The `gpio_read()` macro gives us the current state, but edge triggering also requires knowledge of the **past state** as well as some logic
- Hints: How can we design some code that can call a function _only_ when the button is first clicked? (Rising edge)

#### **Part 3: Misc**

- Create a sprite in the middle of the screen. (Can be in any shape other than simple rectangle) **(@1)**
- It will move to the left for one `CHAR_WIDTH` when `BTN1` is clicked and released,
- move to the right for one `CHAR_WIDTH` when `BTN2` is clicked and released. **(@2 for both short press)**






## Task 2: **Morse Code Generator: Words only**

> Total: 16

You will make a basic morse code input/output using what you've learnt in this tutorial and the online tutorial before.

<img src="image/MorseCode.png" width= "1000" alt="Morse Code"/>

It will only accept morse code for A-Z (ignore numbers or punctuations). Therefore you can assume the maximum of dots and dashes per character is 4. \
The morse code generator will only be change **VALID** morse code strings into flashing lights.


I'll go over some self-defined unofficial terms before I type the same thing over and over again.
> Short Press (Duration < 200ms) \
> Medium Press (Duration > 200ms, < 1000ms) \
> Long Press (Duration > 1000ms) \
> [] (Space character) will be used to represent white space character in places to clearly indicate where white spaces should be.

### Part 1: The Inputs

#### (a) Dots and Dashes

For quality of life and ease of debugging, we want you to display the string of dots and dashes on the TFT screen as you do the inputs.

- When `BTN1` is pressed (short), `". "` is inputted and shown on the TFT screen. **(@1)**
- When `BTN1` is pressed (medium), `"_ "` is inputted and shown on the TFT screen. **(@1)**
```
- For short BTN1 press:
.[]
- For medium BTN1 press:
_[]
- The []s are a visual representation of a white space, in the actual HW, replace '[]' with ' '.
```

*Notice the 1 white space character after the dot and dash, will only give the point if the input and results are **completely** correct.


### Part 2: Validation

Since the intended outputs are only letters, we know that there will only be 4 or less dots or dashes. Therefore we imply a restriction on the input.

- Only a maximum of 4 dots/dashes can be used per character. **(@1)**
```
- If you do 4 short BTN1 presses and 1 medium BTN1 press
. . . . _ WRONG
- Due to the 4 character limitation:
. . . . CORRECT
```

The generator will validate the dot/dash sequence every time a new line is inputted or when the complete input is sent for outputting.

- When `BTN2` is pressed (short), the display goes onto a new line. **(@1)**\
(@1 **only if** after a short BTN2 press, following dots and dashes are applied on a new line)

- Check if the string sequence is valid **(Total @3)**
  - If valid, show the corresponding letter next to the sequence (right side). **(Total @2, each point @1)**
    - @1 for correct letter for all cases, @0.5 if a mix of wrong and correct letters, @0 if does nothing/always gives wrong letter
    - @1 for correct placement of letter (right side of dots/dashes), @0 if wrong position
  - If invalid, delete the entire sequence up til the previous line. **(@1)** (see sample) \
  (@0.5 if delete less or more than required, @0 if nothing is deleted)

#### Sample of what would appear on the TFT screen for 2 sets of responses:
```
- Screen before short press of BTN2
. . . .
- Screen after short press of BTN2
. . . . H

- Screen after more inputs 
. . . . H
. _ _ W

```

#### Sample of invalid inputs:
```
- Screen before short press of BTN2
_ . _ . C
. _ . _
- Screen after short press of BTN2
_ . _ . C

```

Additional functions of buttons:
- When `BTN1` is pressed (long), clear the inputted dots and dashs up to the previous space character. **(@1)** \
(@0.5 if delete less or more than required, @0 if nothing is deleted)
- When `BTN2` is pressed (long), clear everything.  **(@1)** \
(@0.5 if removes something, but not everything)



### Part 3: Outputs

The final part is the final output results

- When `BTN2` is pressed (medium), send the input up for outputting. **(@1)**\
(@1 if LED flashes after this button is pressed + has input on screen, @0 otherwise)

Output goes as follows:
  - Dot: LED on for 250ms
  - Dash: LED on for 750ms
  - Space: LED off for 1750ms
  - Gaps between dots/dashes: LED off for 750ms


When the input is `sent`, output all the listed dot and dash sequences as flashes using any 1 `LED`. **(Total @3, each point @1)**
  - @1 if dots and dashes are correct, @0.5 if length of flashes is inconsistent, @0 if dots and dashes are indistinguishable.
  - @1 if space is correct, @0.5 if length of flashes is inconsistent, @0 if spaces are indistinguishable.
  - @1 if gaps between dots and dashes are correct, @0.5 if length of flashes is inconsistent

After the input is `sent`, clear everything on screen and display the outputted word using latin alphabets. **(Total @3)**
  - @1 if a string of words is displayed on screen
  - @2 if the correct string of words is displayed on screen (with something else)
  - @3 if **ONLY** the correct string is displayed on screen

#### Sample of output
```
- Before BTN2(medium)
_ _ M
_ _ _ O
. _ . R
. . . S
. 
- After BTN2(medium)
MORSE 
- Also flashes MORSE in morse code
```



