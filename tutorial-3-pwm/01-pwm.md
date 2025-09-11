# PWM
Pulse Width Modulation (PWM) is a technology that uses a on-off time of a (periodic) signal to convey information.

We mainly use it to control **servo motors** and DC motors.

## Principle and Terms
REF: ELEC1100 lecture 10 (2022, Deparment of Electronic and Computer Engineering, HKUST) ![](https://i.imgur.com/jnZB3Kd.jpg) ![](https://i.imgur.com/7Iyfnpg.jpg)

## Generating PWM
There are 2 main components when generating a PWM
- Frequency (1 / T)
- On-time (V HIGH time)
  - or Duty Cycle (On-time / T)

In the following parts, we will try to generate a PWM with 50Hz frequency and 1ms on-time.

### Frequency: MCU Clock & Timer 
The MCU Clock is what determines how fast a MCU (/CPU) can operate.

For our boards, they are usually at 84MHz (84 000 000 instructions in a second!).\
But for our purpose, we only need 50Hz.

So we will be using **timers** inside the board to generate a different frequency from the MCU clock.
*Note* a total of 8 timers (`TIM0` - `TIM8`) are available, each can output different frequencies.

#### TIM: PSC & ARR
Each TIMx has some custom parameters that we could set, and we will be using
```c
uint16_t PSC; // Prescaler Value
uint16_t ARR; // Auto Reload Register
```
to slow down the frequency.

- `PSC`: how many **MCU Clock ticks** to wait before increasing **auto-reloaded counter** (`AR counter` from now on cus I'm lazy)\
  i.e. if PSC = 1, output is send every (PSC + 1) MCU Clock cycles: 1st MCU clk tick wait, 2nd tick inc
  
- `ARR`: max value of `AR counter`\
  i.e. if ARR = 1, *counter overflow* triggers when `AR counter` **exceeds (>)** `ARR` value, that is every `ARR + 1` `AR counter` counts\
  and it would be **reset to 0** after overflow.

>Mainly refer to those items in red
>
![](https://imgur.com/YF8xjhF.png)

Therefore the output frequency would be:

$Freqency Output = \frac{Frequency \: of\:clock}{(Prescaler\:Value+1) \cdot (Auto-reloaded\: counter+1)}$

With the frequency set, we would then make use of the `AR counter` value to generate pwm with the desired on-time.

> *Note*: We usually prefer a larger `ARR` value and smaller `PSC` value since it provides better *resolution* - meaning it can generate more "finely divided" on-time values (since more possible counter values). ~~though higher PSC theoretically have lower power consumption, it doesn't really matter~~

> *Extra*: the TIM actually provides much more functionality than just generating PWMs, feel free to explore its parameters and what they do. (NOT NEEDED IN RDC rly)\
[stm32 Timers wiki](https://wiki.st.com/stm32mcu/wiki/Getting_started_with_TIM)

**ClassWork 1**
- [ ] find 3 pairs of `PSC` and `ARR` values to generate a 50Hz output frequency from our board (84GHz).

> Note that PSC & ARR values must be integers.
> You may find prime factorization to be useful.

### On-time: Channels & CCR
We control the on-time by choosing a suitable capture/compare register `CCR` value for the `ARR` we have chosen.

For each TIMx, there are 4 channels `CHx` with their respective `CCRx` values, allowing us to generate PWMs with different on-times of the **same frequency**.

How does it work? A HIGH signal is output if the `CCR` value is greater than value in the `AR counter`, and LOW other wise.

So $duty cycle = \frac{on-time}{T} = \frac{CCR}{ARR+1}$

**ClassWork 2**
- [ ] find the `CCR` value for your 50Hz PWM to have 1ms on-time\
      (just choose 1 set of CCR and ARR values from your classwork 1)

## PWM set up in stm32

### Define the PWM features in the IDE

> There are many pins on the board. You need to find out which pin your `TIMx_CHx` is connected to.

There are 4 steps in setting up the PWM output channel and the pin to use.

1. In catergories, click **Timers** then choose the timer you want to use.

   Setup the **Mode** same as the figure shown. It's fine if you only get 1 channel.

   ![](https://i.imgur.com/53oLWQH.png)
2. Set the **Parameter Settings** same as the figure shown

> Supposedly, You don't have to change anything

![](https://i.imgur.com/aNtON0o.png)&#x20;

3\. **IMPORTANT:** Enable the global interrupt of the timer.

![](https://i.imgur.com/z2MDit3.png)

4. Assign the GPIO pin to be the specific timer and channel. e.g Assign the PC7 pin to output the pwm signal of TIM3\_CH2.

![](https://i.imgur.com/MzvaMDI.png)


### Start Coding!!!

There are 4 steps in coding:

1. Initialize the Timers for PWM

> This should be auto-generated in the beginning of `main.c`

```c
MX_TIM1_Init();
.
.
.
MX_TIM8_Init();
```

2. Set the Prescaler value, Auto Reload Register

```c
// in tutorial3_pwm.c in pwm_init()
TIM1->PSC = 1234;    // set the timer1 prescaler value
TIM1->ARR = 5678;    // set the timer1 auto reload register
```

> Note: `TIM1` stands for Timer 1. but we are using Timer 5 Channel 1 now!!!

> Hint: Use your Classwork 2 answers

3. Start the Timer (in `tutorial3_pwm.c` in `pwm_init()` )

```c
// in tutorial3_pwm.c in pwm_init()
HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); 
// HAL_TIM_PWM_Start(timer, channel);
// htim1 refers to timer 1
// We are using timer 5 channel 1!!!
```

> Hint:  `&htim1` means Timer 1, remember to change to Timer 5

4. Change the CCR as required for the classwork/homework

```c
TIM1->CCR1 = 321; //set the compare value of timer1 channel1
TIM1->CCR2 = 678; //set the compare value of timer1 channel2
```

> Hint: Use your Classwork 2 answers

#### Use the skeleton code `tutorial3_pwm.c` located in the`src` file!!

```c
// add the below in main.c
...
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* add the following 3 lines*/
void pwm_init(void); //add this line!
void pwm_classwork(void); //add this line!
void pwm_homework(void); //add this line!

/* USER CODE END PFP */
...
pwm_init(); //add this line!

while (1) {
    pwm_classwork(); //add this line!
}   
...
```

Now test your PWM with a servo motor!

[Servo Motor](PWM_Servo.md#connections)
