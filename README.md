# Arduino Two-Way Traffic Light Controller

Arduino-based two-way traffic light controller using timer-based control and an external interrupt for a programmed pedestrian/special mode.

## Overview

This project implements a two-way traffic light system using an Arduino UNO. Red, yellow and green LEDs represent the signals for two traffic directions.

The controller normally follows an automatic sequence using timer-based control. A push button connected to an external interrupt can trigger a programmed special mode when required.

## Objectives

- Design a two-way traffic light control system.
- Automate the switching between RED, YELLOW and GREEN signals.
- Use timer-based control for predictable signal transitions.
- Use an external interrupt to respond to a push-button input.
- Simulate and test the complete system using Tinkercad.

## Components Used

- Arduino UNO
- Red LEDs
- Yellow LEDs
- Green LEDs
- Push button
- Resistors
- Breadboard
- Jumper wires

## Working Principle

The system operates through a predefined sequence of traffic states for two directions.

1. One direction is given the GREEN signal while the other remains RED.
2. After the required time, the active GREEN signal changes to YELLOW.
3. The signal then changes to RED and the other direction is allowed to proceed.
4. The timer controls the duration of each state, allowing the sequence to continue automatically.
5. When the push button is pressed, the external interrupt allows the Arduino to detect the event immediately.
6. The programmed special/pedestrian mode is then executed, that is both the signals turn red for pedestrian crossing.
7. Once the special mode is completed, normal traffic operation resumes.

## Timer-Based Control

The timer is used to control how long each traffic signal remains active.

- Provides consistent timing between signal changes.
- Allows the normal traffic sequence to run automatically.
- Reduces dependence on repeated manual input.
- Restarts the sequence after a complete cycle.

## External Interrupt

The push button is connected to an interrupt input of the Arduino.

When the button is pressed, the interrupt allows the controller to respond without waiting for the normal loop to complete. This is used to enter the programmed special mode before returning to normal traffic operation.

## Traffic States

The controller was tested for different traffic conditions:

- `Road 1 RED → Road 2 GREEN`
- `Road 1 YELLOW → Road 2 RED`
- `Road 1 GREEN → Road 2 RED`
- `Pedestrian / Special Mode Road 1 RED  Road 2 Red`

## Simulation

The complete circuit was designed and tested in Tinkercad. The simulation was used to verify the LED sequence, timer-based transitions and push-button interrupt response.

## Project Files

- `TrafficLightController.ino` – Arduino program implementing the traffic sequence, timer control and interrupt-based special mode.
- `screenshots/` – Contains the circuit and simulation screenshots for different traffic states.

## Technologies Used

- Arduino UNO
- Arduino IDE
- Tinkercad Circuits
- Timer-based control
- External interrupts
- Digital LED control

## Conclusion

The two-way traffic light controller was successfully designed and simulated using Arduino UNO. The project demonstrates how timer-based control can be used for automatic traffic signal operation, while an external interrupt provides a quick response to an external button press.

The complete circuit was tested in Tinkercad and the observed signal transitions matched the intended operation.

## Tinkercad Simulation

The complete circuit and simulation are available on Tinkercad.

**Tinkercad Link:**
https://www.tinkercad.com/things/fODba7Y9RrC-traffic-light-controller-using-timer-interrupts-anjali-kk

## Project Repository

The complete Arduino code, circuit screenshots and simulation results are available in this repository.
