# Homework

[Back to Main](./README.md) | [Previous Page](./03-classwork.md)

## Task 1: Real-Time Button Status via Bluetooth

Configure your STM32 board to continuously send the status of all buttons to your computer using the HC-05 Bluetooth module.
Format the data packet as follows:

`[Button 1: On/Off], [Button 2: On/Off], ...`

## Task 2: Bluetooth-Controlled Stopwatch

Implement a stopwatch on your STM32 board.
Your program should receive two commands via Bluetooth:

- `s`: Start/stop/resume the stopwatch
- `r`: Reset the stopwatch

After receiving each command, echo the command back to the computer via Bluetooth.
Update the time on the TFT monitor every millisecond.

![](./image/stopwatch.jpg)

[Back to Main](./README.md) | [Previous Page](./03-classwork.md)
