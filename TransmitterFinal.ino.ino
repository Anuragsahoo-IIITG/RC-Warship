#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include<printf.h>

// Pins for Joystick and Potentiometers
const int joyXPin = A0;  // Joystick X-axis for direction
const int joyYPin = A1;  // Joystick Y-axis for throttle
const int pot1Pin = A3;  // Potentiometer 1 for Servo 1
const int pot2Pin = A4;  // Potentiometer 2 for Servo 2
const int joySwitch = 8; // Fire button switch
//const int joySwitchm = 6;

// Create the RF24 radio object
RF24 radio(9, 10); // CE, CSN pins

// Radio pipe addresses (same for both transmitter and receiver)
const byte address[6] = "00001";

struct Data_Packet {
  int xValue;
  int yValue;
  int servo1Pos;
  int servo2Pos;
  int fireGun; 
};

Data_Packet data;

// Debounce variables
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // 50ms debounce delay
int lastButtonState = HIGH;
int buttonState;

// // Mode Variables
// unsigned long lastDebounceTimem = 0;
// unsigned long debounceDelaym = 50; // 50ms debounce delay
// int lastButtonStatem = HIGH;
// int buttonStatem;
// int Mode = HIGH;

void setup() {
  Serial.begin(9600);

  // Initialize joystick and potentiometer pins
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);
  pinMode(pot1Pin, INPUT);
  pinMode(pot2Pin, INPUT);
  pinMode(joySwitch, INPUT_PULLUP);
//  pinMode(joySwitchm, INPUT_PULLUP);

  // Initialize NRF24L01
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH); // High Power for long range
  radio.stopListening(); // Set as transmitter

  printf_begin();

  radio.printDetails();

}

void loop() {
  // Read joystick and potentiometer values
  data.xValue = analogRead(joyXPin);
  data.yValue = analogRead(joyYPin);
  data.servo1Pos = analogRead(pot1Pin);
  data.servo2Pos = analogRead(pot2Pin);

  // Debounce the fire button
  int reading = digitalRead(joySwitch);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      data.fireGun = buttonState;  // Update fireGun state only after debounce
    }
  }
  lastButtonState = reading;

  //  // Debounce the fire Mode Button
  // int readingm = digitalRead(joySwitchm);
  // if (readingm != lastButtonStatem) {
  //   lastDebounceTimem = millis();
  // }
  // if ((millis() - lastDebounceTimem) > debounceDelaym) {
  //   if (readingm != buttonStatem) {
  //     buttonStatem = readingm;
  //     if(buttonStatem == LOW)
  //     Mode = !Mode;  // Update fireGun state only after debounce
  //   }
  // }
  // lastButtonStatem = readingm;
  //   data.fireMode = Mode;
  
  // Send the data
  radio.write(&data, sizeof(Data_Packet));

  // Optional debug output
  // Serial.print("xValue: "); Serial.print(data.xValue);
  // Serial.print(" | yValue: "); Serial.print(data.yValue);
  // Serial.print(" | Servo1: "); Serial.print(data.servo1Pos);
  // Serial.print(" | Servo2: "); Serial.print(data.servo2Pos);
  // Serial.print(" | FireGun: "); Serial.println(data.fireGun);
  //Serial.print(" | FireMode: ");Serial.println(data.fireMode);

  delay(50); // Delay to prevent spamming
}
