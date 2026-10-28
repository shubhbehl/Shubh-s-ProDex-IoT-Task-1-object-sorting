# Automatic Object Sorting System

## 1. Introduction

For this ProDex IoT task, I built an object sorting system using Arduino and Tinkercad. The idea is to detect an object, estimate its length, and sort it into one of three categories using a servo motor.

The original task was based on colour detection using a TCS3200 sensor. However, since that sensor was not available in Tinkercad, I changed the approach to length-based sorting using an ultrasonic sensor.

The circuit includes an Arduino Uno, an HC-SR04 ultrasonic sensor, an L293D motor driver, a DC motor, and a servo motor.

## 2. Components Used

| Component                 | What it does                                      |
| ------------------------- | ------------------------------------------------- |
| Arduino Uno R3            | Controls the system and processes sensor readings |
| HC-SR04 ultrasonic sensor | Measures distance and detects the target          |
| L293D motor driver        | Allows the Arduino to control the DC motor        |
| DC motor                  | Represents the conveyor belt motor                |
| Servo motor               | Moves the diverter to sort objects                |
| Tinkercad Circuits        | Used to build and test the circuit virtually      |

## 3. Circuit Connections

### Ultrasonic Sensor

| Sensor Pin | Connected To   |
| ---------- | -------------- |
| VCC        | Arduino 5V     |
| GND        | Arduino GND    |
| TRIG       | Digital pin 9  |
| ECHO       | Digital pin 10 |

### L293D Motor Driver

| L293D Pin      | Connected To          |
| -------------- | --------------------- |
| Pin 1          | Arduino digital pin 5 |
| Pin 2          | Arduino digital pin 6 |
| Pin 3          | First motor terminal  |
| Pins 4 and 5   | GND                   |
| Pin 6          | Second motor terminal |
| Pin 7          | Arduino digital pin 7 |
| Pin 8          | Motor supply          |
| Pins 12 and 13 | GND                   |
| Pin 16         | Arduino 5V            |

### Servo Motor

| Servo Wire | Connected To          |
| ---------- | --------------------- |
| Signal     | Arduino digital pin 3 |
| VCC        | Arduino 5V            |
| GND        | Arduino GND           |

## 4. How the System Works

The ultrasonic sensor sends out a sound pulse and measures how long its echo takes to return. The Arduino uses this information to calculate the distance to the target.

When the target enters the detection zone, the program records the start time. When it leaves the zone, the Arduino calculates how long it was detected.

The program then estimates the object's length using:

$$
L = v \times t
$$

Here, \(L\) is the estimated length, \(v\) is the conveyor speed, and \(t\) is the time for which the object was detected.

The current code assumes a conveyor speed of 5 cm/s. In a real setup, this value would have to be measured and adjusted according to the actual conveyor speed.

## 5. Sorting Logic

After estimating the length, the program assigns the object to one of three categories.

| Estimated Length        | Category | Servo Position |
| ----------------------- | -------- | -------------- |
| Less than 5 cm          | Short    | 120°           |
| 5 cm to less than 10 cm | Medium   | 90°            |
| 10 cm or more           | Long     | 60°            |

The servo moves to the position assigned to that category and then returns to its neutral position. The Arduino also updates the count for the corresponding category and displays the results in the Serial Monitor.

## 6. Code Overview

I divided the program into separate functions to keep the code organised and easier to understand.

* `getDistance()` reads the ultrasonic sensor and calculates the distance.
* `startConveyor()` starts the DC motor.
* `stopConveyor()` stops the motor.
* `sortObject()` classifies an object and moves the servo to the required position.
* `showCounts()` displays the number of objects in each category.
* `setup()` configures the pins and initialises the components.
* `loop()` repeatedly reads the sensor and checks whether the target enters or leaves the detection zone.

The `Servo.h` library is used to control the servo motor. The `pulseIn()` function measures the ultrasonic echo, while `millis()` measures elapsed time.

## 7. Testing in Tinkercad

I built the circuit in Tinkercad and tested the main components individually before running them together.

During testing, I checked that:

* The ultrasonic sensor readings changed when I moved the target.
* The DC motor rotated when controlled through the L293D.
* The servo moved to the required positions.
* The program detected changes in the target's detection state and calculated the detection duration.

The Serial Monitor was useful for checking sensor readings and observing the program's output.

## 8. Limitations

One limitation of this project is that Tinkercad does not animate an object moving along the conveyor in my setup. I therefore moved the ultrasonic sensor's target manually to test the detection logic.

Because of this, the program measures how long the target remains inside the detection zone and uses that time to estimate its length. It does not directly measure the physical length of an object.

For this method to work accurately in a real system, the conveyor speed must be calibrated, and the sensor must reliably detect the front and rear edges of each object. The detection threshold and sensor position would also need to be adjusted.

## 9. Possible Applications

The same basic idea could be used in several practical systems:

* Sorting packages according to their approximate size.
* Separating products on manufacturing lines.
* Assisting automated packaging systems.
* Handling packages in warehouses.
* Learning and developing embedded control systems that combine sensors and motors.

For a real conveyor, an encoder could be added to measure belt movement and improve the accuracy of the length calculation.

## 10. Conclusion

This project helped me explore how an Arduino can use sensor readings to make decisions and control motors automatically.

The circuit combines ultrasonic sensing, time measurement, conditional logic, a DC motor, and a servo-operated diverter. Although Tinkercad cannot reproduce a moving conveyor in this setup, I was able to test the electronic components and demonstrate the basic detection and control logic.

Further calibration and testing with a physical conveyor would be needed before the system could reliably sort real objects by length.
