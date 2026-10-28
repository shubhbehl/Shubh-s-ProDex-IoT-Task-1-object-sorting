#include <Servo.h>

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// L293D motor driver pins
const int motorEnable = 5;
const int motorIn1 = 6;
const int motorIn2 = 7;

// Servo signal pin
const int servoPin = 3;

Servo sorter;

// Adjust these values according to your setup
const float conveyorSpeed = 5.0;  // cm per second
const float detectionLimit = 300.0;

// Length limits for sorting
const float shortLimit = 5.0;
const float mediumLimit = 10.0;

// Servo positions
const int shortPosition = 120;
const int mediumPosition = 90;
const int longPosition = 60;

// Motor speed (0 to 255)
const int motorSpeed = 200;

// Number of objects in each bin
int shortObjects = 0;
int mediumObjects = 0;
int longObjects = 0;

// Used to track an object passing the sensor
bool objectPresent = false;
unsigned long objectStart = 0;
unsigned long lastReading = 0;

// Measure the distance using the ultrasonic sensor
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration * 0.0343 / 2.0;
}

// Start the conveyor motor
void startConveyor() {
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorEnable, motorSpeed);
}

// Stop the conveyor motor
void stopConveyor() {
  analogWrite(motorEnable, 0);
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
}

// Display the number of sorted objects
void showCounts() {
  Serial.println("\n--- Sorting Results ---");

  Serial.print("Short: ");
  Serial.println(shortObjects);

  Serial.print("Medium: ");
  Serial.println(mediumObjects);

  Serial.print("Long: ");
  Serial.println(longObjects);

  Serial.print("Total: ");
  Serial.println(shortObjects + mediumObjects + longObjects);
}

// Sort an object based on its calculated length
void sortObject(float length) {
  int servoPosition;

  Serial.println("\nObject detected and measured!");

  Serial.print("Length: ");
  Serial.print(length, 2);
  Serial.println(" cm");

  if (length < shortLimit) {
    Serial.println("Bin: Short");
    servoPosition = shortPosition;
    shortObjects++;
  }
  else if (length < mediumLimit) {
    Serial.println("Bin: Medium");
    servoPosition = mediumPosition;
    mediumObjects++;
  }
  else {
    Serial.println("Bin: Long");
    servoPosition = longPosition;
    longObjects++;
  }

  // Pause the conveyor while the object is sorted
  stopConveyor();

  sorter.write(servoPosition);
  delay(1000);

  // Return the diverter to its normal position
  sorter.write(mediumPosition);
  delay(500);

  showCounts();
  startConveyor();
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motorEnable, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

  sorter.attach(servoPin);
  sorter.write(mediumPosition);

  Serial.println("Object Sorting System Started");
  Serial.println("Short: less than 5 cm");
  Serial.println("Medium: 5 cm to less than 10 cm");
  Serial.println("Long: 10 cm or more");

  startConveyor();
}

void loop() {
  // Take a reading every 30 milliseconds
  if (millis() - lastReading < 30) {
    return;
  }

  lastReading = millis();

  float distance = getDistance();

  // Ignore readings when no echo is received
  if (distance < 0) {
    return;
  }

  bool detected = distance < detectionLimit;

  // Record when the object first appears
  if (detected && !objectPresent) {
    objectPresent = true;
    objectStart = millis();

    Serial.println("Object entering sensor range");
  }

  // Calculate the length when the object leaves
  if (!detected && objectPresent) {
    objectPresent = false;

    unsigned long timeTaken = millis() - objectStart;
    float timeInSeconds = timeTaken / 1000.0;

    // Length = conveyor speed x detection time
    float length = conveyorSpeed * timeInSeconds;

    if (timeTaken >= 50) {
      sortObject(length);
    }
  }
}