# Automatic Object Sorting System

## About the Project

This project is part of the ProDex IoT task. The aim is to build a simple automatic sorting system using Arduino and Tinkercad.

The original task required sorting objects based on colour using a TCS3200 colour sensor. Since the sensor was not available in Tinkercad, I adapted the project to demonstrate length-based sorting using an ultrasonic sensor.

The system detects an object, estimates its length, and uses a servo motor to direct it towards the appropriate sorting category.

## Components Used

* Arduino Uno R3
* HC-SR04 ultrasonic sensor
* L293D motor driver
* DC motor
* Servo motor
* Tinkercad Circuits

## How It Works

The ultrasonic sensor measures the distance to the target. The Arduino detects when the target enters and leaves the configured detection zone and records the time taken.

The program estimates the object's length using the detection duration and a configured conveyor speed. Based on the estimated length, the servo motor moves to the corresponding position.

The number of objects assigned to each category is displayed in the Serial Monitor.

## Sorting Categories

| Estimated Length        | Category | Servo Position |
| ----------------------- | -------- | -------------- |
| Less than 5 cm          | Short    | 120°           |
| 5 cm to less than 10 cm | Medium   | 90°            |
| 10 cm or more           | Long     | 60°            |

## Circuit

The circuit was designed and tested in Tinkercad Circuits.

![Complete Circuit](screenshots/01_complete_circuit.png)

**Tinkercad simulation:** PASTE_YOUR_TINKERCAD_LINK_HERE

## Source Code

The Arduino code is included in this repository in the `.ino` file.

## Limitations

Tinkercad does not animate an object moving along the conveyor in this setup, so the ultrasonic sensor's target has to be moved manually during testing.

The current program estimates length from the time the target remains inside the detection zone, assuming a conveyor speed of 5 cm/s. This demonstrates the measurement approach, but it does not verify the actual physical length of an object. A real system would require a calibrated conveyor speed and suitable sensor positioning.

## Real-World Applications

This type of system could be adapted for sorting packages by size, product inspection on manufacturing lines, packaging automation, and warehouse handling.

## Project Documentation

Detailed information about the circuit connections, working principle, implementation, and limitations will be included in the `docs/project_documentation.md` file.
