# Bluetooth

[Back to Main](./README.md) | [Previous Page](./01-uart.md)

> Author: Ken Law (cclawad@connect.ust.hk)

## Introduction

The HC-05 Bluetooth module, like other Bluetooth devices, has a default device name and password. Since many identical HC-05 modules are used in the lab, it’s important to customize the name and password to easily identify your module.

## Setting Up Your Bluetooth Module

To configure your HC-05 module, follow these steps:

0. Connect the HC-05 and the USB-TTL module together (remember TX to RX and the 3.3V)
1. Hold down the button on the HC-05 while plugging the USB-TTL adapter into your computer.
1. Release the button. The HC-05 should enter "AT" mode, indicated by a slowly flashing LED.
1. Set your serial monitor baud rate to 38400 and connect. If this doesn’t work, try 9600.
1. Type `AT` and press Enter. If you receive an `OK` response, you can proceed with the AT commands below. If not, repeat the steps above.
1. Some commands (e.g., `AT+NAME=...` or `AT+NAME?`) may require you to hold the button while pressing Enter.
1. AT commands are **case-sensitive**.

**Useful AT Commands:**

- `AT`: Test connection
- `AT+RESET`: Return to normal mode (does not reset configuration)
- `AT+NAME?`: Show current device name
- `AT+NAME=<Param>`: Set device name
- `AT+PSWD?`: Show current password
- `AT+PSWD=<Param>`: Set password
- `AT+UART=<baud>,<stop>,<parity>`: Set UART settings (recommended: `AT+UART=115200,0,0`)
- `AT+UART?`: Show UART settings
- `AT+ROLE=<Param>`: Set role (0 = Slave, 1 = Master)
- `AT+ROLE?`: Show current role
- `AT+CMODE=<Param>`: Set connection mode (0 = specified device, 1 = any device)
- `AT+CMODE?`: Show connection mode
- `AT+ORGL`: Reset all settings to default

> **HC-05 AT Command Manual:** [PDF](https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf)

> **HC-08 AT Command Manual (Reference):** [PDF](https://www.rhydolabz.com/documents/30/hc05_bluetooth.pdf)

### AT Command Configuration Steps

1. Set the baud rate to 38400 in CoolTerm (default for configuration).
2. Connect and test with `AT` (try 9600 if 38400 fails).
3. Check and set the module name.
4. Check and set the password.
5. Set the module role to Slave (your computer acts as Master).
6. Set connection mode to 1 (allows connection to any nearby device).

After configuration, connect the HC-05 to the UART port of your STM32 board. Once powered, your computer should detect the device.

> If you’re using Windows 11 and cannot find the HC-05, see this [troubleshooting guide](./02a-bluetooth-problem-solving-win11.md).

After pairing, rescan the serial ports in CoolTerm. The port that takes longer to connect is usually the correct one, as your computer waits for the HC-05 to respond.

## MIT App Inventor (Bonus)

For future robotics projects, you may need to build your own robot controller. MIT App Inventor (https://appinventor.mit.edu/) is a free online tool for creating Android apps without coding experience. You can easily design controller interfaces (joysticks, buttons) and use the built-in Bluetooth Client library to communicate with your robot.

For more details, see the [Bluetooth Client documentation](http://ai2.appinventor.mit.edu/reference/components/connectivity.html#BluetoothClient).

> Explore YouTube tutorials and online resources to learn more about MIT App Inventor.

[Previous](./01-uart.md) | [Next Page](./03-classwork.md)
