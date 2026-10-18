# CAN-Based Automotive Dashboard System

## Overview

This project implements a CAN (Controller Area Network) based automotive dashboard using PIC microcontrollers and Embedded C.

The system consists of three Electronic Control Units (ECUs) that communicate with each other over the CAN bus to exchange vehicle parameters such as speed, gear position, engine RPM, and indicator status. The received information is displayed on a character LCD.

## Features

- CAN communication between multiple ECUs
- Speed monitoring using ADC
- Gear selection using digital keypad inputs
- Engine RPM monitoring
- Indicator control
- CAN message transmission and reception
- Real-time dashboard display using CLCD
- Modular driver implementation in Embedded C

## System Architecture

### ECU 1 – Speed and Gear Control

- Reads analog input for vehicle speed.
- Accepts keypad input for gear selection.
- Transmits speed and gear information through CAN.

### ECU 2 – RPM and Indicator Control

- Reads analog input for engine RPM.
- Processes indicator-related keypad inputs.
- Transmits RPM and indicator status through CAN.
- Includes an engine temperature input function.

### ECU 3 – Dashboard Display

- Receives CAN messages from ECU 1 and ECU 2.
- Identifies messages using predefined CAN IDs.
- Displays vehicle parameters on a character LCD.

## CAN Message IDs

| Parameter | CAN ID |
|---|---|
| Speed | `0x10` |
| Gear | `0x20` |
| RPM | `0x30` |
| Engine Temperature | `0x40` |
| Indicator Status | `0x50` |

## Hardware Requirements

- PIC microcontroller(s) with CAN support
- CAN transceiver(s)
- Character LCD (CLCD)
- Digital keypad or switches
- Analog input sources or sensors
- Indicator LEDs
- Power supply and connecting wires

## Software Requirements

- MPLAB X IDE
- MPLAB XC8 Compiler
- PIC device support packages
- Compatible PIC programmer/debugger
- Circuit simulator (optional)

## Project Structure

```text
CAN_project_INT_26001C/
├── ECU1_headers/
│   ├── ecu1_main.c
│   ├── ecu1_sensor.c
│   ├── ecu1_sensor.h
│   ├── adc.c
│   ├── adc.h
│   ├── can.c
│   ├── can.h
│   ├── digital_keypad.c
│   ├── digital_keypad.h
│   ├── msg_id.h
│   ├── uart.c
│   └── uart.h
│
├── ECU2_headers/
│   ├── ecu2_main.c
│   ├── ecu2_sensor.c
│   ├── ecu2_sensor.h
│   ├── adc.c
│   ├── adc.h
│   ├── can.c
│   ├── can.h
│   ├── digital_keypad.c
│   ├── digital_keypad.h
│   ├── msg_id.h
│   ├── uart.c
│   └── uart.h
│
└── Dashboard_ECU3_headers/
    ├── main.c
    ├── message_handler.c
    ├── message_handler.h
    ├── can.c
    ├── can.h
    ├── clcd.c
    ├── clcd.h
    ├── timer0.c
    ├── timer0.h
    ├── msg_id.h
    ├── uart.c
    └── uart.h
```

## Working Principle

1. Each ECU initializes the peripherals required for its operation.
2. ECU 1 reads speed and gear inputs and transmits the corresponding data over CAN.
3. ECU 2 reads RPM and indicator inputs and transmits the corresponding information over CAN.
4. ECU 3 receives the CAN messages and identifies them using their message IDs.
5. The dashboard updates the LCD with the received vehicle parameters.

## How to Build and Run

1. Open MPLAB X IDE.
2. Create or open a project for the target PIC microcontroller.
3. Configure the device settings, oscillator frequency, and configuration bits.
4. Add the relevant source and header files for each ECU.
5. Build each ECU firmware separately.
6. Program the firmware onto the corresponding PIC microcontrollers.
7. Connect the ECUs through the CAN transceivers.
8. Ensure that the CAN bit rate, message IDs, and payload formats match across all ECUs.
9. Test the inputs, CAN communication, and LCD output.

## Learning Outcomes

- Embedded C programming
- PIC microcontroller interfacing
- ADC configuration and analog input processing
- Digital keypad interfacing
- CAN protocol and inter-ECU communication
- LCD interfacing
- Modular embedded software development
- Hardware and firmware debugging

## Future Improvements

- Integrate real automotive sensors.
- Add fault detection for CAN communication.
- Add more vehicle parameters to the dashboard.
- Implement diagnostic features for ECU communication.

## Author

**Manoj B.**
