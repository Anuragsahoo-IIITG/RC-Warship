
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>  // Include the Servo library
#include<printf.h>

const int relayPin = 2;

// Motor pins (connect these to your motor driver)
const int motor1Pin1 = 6;  // IN1
const int motor1Pin2 = 7;  // IN2
const int motor2Pin1 = 8;  // IN3
const int motor2Pin2 = 4;  // IN4
const int motor1EnablePin = 3;  // ENA
const int motor2EnablePin = 5;  // ENB

// Servo motors
Servo servo1;
Servo servo2;
const int servo1Pin = A1;  // Servo 1 PWM pin
const int servo2Pin = A0;  // Servo 2 PWM pin

RF24 radio(9, 10); // CE, CSN pins

// Radio pipe addresses
const byte address[6] = "00001";

struct Data_Packet {
  int xValue;
  int yValue;
  int servo1Pos;
  int servo2Pos;
  int fireGun; 
};

Data_Packet data;

void setup() {
  Serial.begin(9600);

  // Motor pins setup
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  //digitalWrite(motor1Pin1, LOW);
  //digitalWrite(motor1Pin2, LOW);
  //digitalWrite(motor2Pin1, LOW);
  //digitalWrite(motor2Pin2, LOW);

  // Initialize servos
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);

    // Relay pin setup
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Ensure gun is off initially

  // Initialize NRF24L01
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_HIGH); // High Power for long range
  radio.startListening(); // Set as receiver

   printf_begin();

   radio.printDetails();
}

void loop() {
  // Check if data is available
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Packet));

    Serial.print("Fire : ");Serial.println(data.fireGun);

    // Map joystick values to motor control (-255 to 255)
    int motorSpeed = map(data.yValue, 0, 1023, -255, 255);
    int steering = map(data.xValue, 0, 1023, -255, 255);

    // Control the motors
    controlMotors(motorSpeed, steering);

    // Map and control servos (values from 0 to 180 degrees)
    int servo1Angle = map(data.servo1Pos , 0, 1023, 0, 180);
    int servo2Angle = map(data.servo2Pos , 0, 1023, 0, 180);//395 to 627

    servo1.write(servo1Angle);
    servo2.write(servo2Angle);

        // Control the electric gun using the relay
    if (data.fireGun == 0) {
      digitalWrite(relayPin, HIGH);  // Turn on the relay (fire the gun)
      delay(50);
    } else {
      digitalWrite(relayPin, LOW);   // Turn off the relay (stop firing the gun)
    }

  }
}

void controlMotors(int speed, int turn) {
  int leftMotorSpeed = constrain(speed + turn, -255, 255);
  int rightMotorSpeed = constrain(speed - turn, -255, 255);

  // Set left motor
  if (leftMotorSpeed > 0) {
    analogWrite(motor1EnablePin, leftMotorSpeed);
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
  } else {
    analogWrite(motor1EnablePin, -leftMotorSpeed);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
  }

  // Set right motor
  if (rightMotorSpeed > 0) {
    analogWrite(motor2EnablePin, rightMotorSpeed);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
  } else {
    analogWrite(motor2EnablePin, -rightMotorSpeed);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
  }
}
