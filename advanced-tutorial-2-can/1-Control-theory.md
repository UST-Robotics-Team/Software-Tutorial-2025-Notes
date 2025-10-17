# Control Theory

## Quick Teleporter

1. [Introduction](1-Control-theory.md#introduction)
2. [Control Types](1-Control-theory.md#control-type)
3. [Fuzzy Control](1-Control-theory.md#fuzzy-control)
4. [PID Theory](1-Control-theory.md#pid-theory)

## Introduction
Before geting into the actual theory, lets first start with the basic physical quantity first.

| Name | Symbol | Definition | Formula |
| --- | --- | --- | --- |
| Displacement | $s$ | position offset from the origin | $s$ |
| Velocity | $v$ | position change over time | $\frac{\triangle s}{\triangle t}$ |
| Acceleration | $a$ | velocity change over time | $\frac{\triangle v}{\triangle t}$ |
| Angular displacement | $\theta$ | angle offset from the origin | $\theta$ |
| Angular velocity | $w$ | angle change over time | $\frac{\triangle \theta}{\triangle t}$ |
| Torque | $\tau$ | angle velocity change over time | $\frac{\triangle w}{\triangle t}$ |

> These are simple physical quantity that you may need to consider when performing calculation. We will use these as an explaination soon.

But why we need to know these physical quantity? Because we need to know what exactly we can control.

**Life is not a game, you can not teleport. There exist an process from your control from one place to another.**

## Control type
There are generally two types of control method, which both are actually feasible to perform.

![](<image/Control system.gif>)

### open-loop control
This control method simply intake control signal with a **pre-defined** trajectory and control the mechanism.

---

### closed-loop control
This control method take the feedback as a reference, and **dynamically modify** the trajectory and make control.

---

For example: \
The ELCP Motor (provided for you as mechanism) can be used as **open-loop control** as it is **velocity control**.

The RM Motor (provided for you as wheelbase) can be used as **close-loop control** as it is **current control** (which generates torque).

## Fuzzy Control
This control is a simple **close-loop** control method.

This has a simple logic, convert the motor status into numerous, blurry status (e.g. )

Lastly, it is all about `if then else`, you can directly define different behavior under different scenario.

e.g. \
Consider the following cases:
| Category | Value |
| --- | --- |
| Input | Current / Torque of motor |
| Feedback | Current speed of motor |
| Desired Output | Target speed of motor |

In this cases, we can simply defines the following: \
Divides the error (target - current) into different cases:\
| Case | Performance |
| --- | --- |
| Between 0.1 rps | 20% current output |
| Between 1 rps | 60% current output |
| Between 10 rps | 80% current output |
| Otherwise | 100% current output |

---

* Pros: Extremely easy and fast, no precise model needed
* Cons: Very shaking results, it might not be accurate

## PID Theory
PID is a more advanced and preferred control logic, as it doesn't rely on "blurry" concepts, and gives a better intuitive on how it is playing.

Generally, **Fuzzy is easy, but PID is more accurate**

This part will be covered in the next page :>
