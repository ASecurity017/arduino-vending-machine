# Coke Machine — Finite State Machine on Arduino Nano Every

An embedded systems project implementing a classic vending machine as a **Finite State Machine (FSM)**, built on an Arduino Nano Every. The system accepts simulated coin input via push-buttons, tracks accumulated credit, dispenses a product once the price threshold is met, and returns change — all reflected live on an I2C LCD display.


## Overview

- **Coin input:** 3 push-buttons representing 5c, 20c, and 50c coins, plus a 4th button to return accumulated change
- **Product price:** 100 cents (configurable constant)
- **Live feedback:** 2x16 I2C LCD shows current credit, return change amount, and LED status in real time
- **Output indicators:** LEDs signal when a product is dispensed and when change is returned

## State Machine Design

The FSM moves through the following states based on button events (falling-edge triggered) and accumulated credit:

`Idle → 5¢ / 20¢ / 50¢ → Coke Product → Return Change → Exit → _Quit_`

- Coin presses accumulate credit (`Change_In`) at any point in `Idle`
- Once `Change_In ≥ Coke_Price`, the system enters **Coke Product**, turns on the Coke LED, then routes to **Return Change** (if overpaid) or straight to **Exit** (if exact)
- Pressing the Return Change button at any time in `Idle` short-circuits to **Return Change**, calculating and displaying any owed amount before exiting

## Hardware

| Component | Role |
|---|---|
| Arduino Nano Every | Microcontroller / FSM logic |
| 4x Momentary Push-Buttons | Coin input (internal pull-up, active-low, falling-edge detection) |
| 2x LEDs (220Ω) | Coke-dispensed indicator / Change-returned indicator |
| I2C 16x2 LCD | Live credit, return amount, and LED status display |
| Breadboard + jumper wires | Circuit assembly |

| Signal | Pin | Function |
|---|---|---|
| B1 (5¢) | DI2 | Add 5 cents credit |
| B2 (20¢) | DI4 | Add 20 cents credit |
| B3 (50¢) | DI6 | Add 50 cents credit |
| B4 (Return) | DI8 | Return accumulated credit |
| Coke LED | DO13 | ON when `Change_In ≥ Coke_Price` |
| Change LED | DO12 | ON when `Return_Change > 0` |

## LCD Output Format

```
CREDIT:XXX COKE:X
RETURN:XXX CHNG:X
```

Example — after inserting 115 cents against a 100-cent price:

```
CREDIT:115 COKE:1
RETURN:015 CHNG:1
```

## Implementation Notes

- States are modeled with an `enum` and driven through a nested `switch(currentState)` structure
- Button inputs use falling-edge detection (`INPUT_PULLUP`, active-low) to register exactly one event per physical press
- LCD updates run every iteration of the main loop via I2C (SDA/SCL)
- Timing (state hold, LED duration, credit reset) was benchmarked against the original LabVIEW/myRIO reference implementation

## Skills Demonstrated

- Finite state machine design and translation from a graphical toolkit (LabVIEW) into embedded C
- Real-time hardware I/O: debounced digital input handling, output control, and I2C peripheral communication
- Systematic hardware debugging and test-driven verification against a reference behaviour spec

## Image of the hardware of the project
<img width="1257" height="827" alt="image" src="https://github.com/user-attachments/assets/02f49631-cb92-4a68-b486-31ad95f7b1c5" />




