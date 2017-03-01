#include "Arduino.h"

#define switchTime 500
#define sleepAfterSwitch 2000

#define relayPin 7
#define sensorPin 5

#define sensorPinUpState false
#define relayPinUpSwitchesOn false

bool lastSensorState;
unsigned long lastTimeStamp;

void setup() {
//  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  reset();
}

void loop() {
  performActions();
}

void reset() {
  switchOff();
  lastSensorState = false;
}

void performActions() {
//  Serial.println("lastSensorState: " + String(lastSensorState) + ", lastTimeStamp: " + lastTimeStamp + ", state: " + getState());

  if (checkSensor()) {
    // sensoring something
    if (!lastSensorState) {
      lastTimeStamp = millis();

      lastSensorState = true;
    } else {
      if (millis() - lastTimeStamp >= switchTime) {
//        Serial.println(millis() - lastTimeStamp);

        lightSwitch();
        delay(max(sleepAfterSwitch - switchTime, 0));
        lastTimeStamp = millis();
      } else {
        // do nothing
      }
    }
  } else {
    // not sensing anything
    lastSensorState = false;
  }
}

bool checkSensor() {
//  Serial.print("x = " + String(digitalRead(relayPin)));
//  Serial.print(", c = " + String(relayPinUpSwitchesOn));
//  Serial.println(" => " + String(digitalRead(relayPin) ^ !relayPinUpSwitchesOn));
  return (digitalRead(sensorPin) ^ !sensorPinUpState);
}

void lightSwitch() {
  digitalWrite(relayPin, !(getState() ^ !relayPinUpSwitchesOn));
}

void switchOn() {
  digitalWrite(relayPin, relayPinUpSwitchesOn);
}

void switchOff() {
  digitalWrite(relayPin, !(relayPinUpSwitchesOn));
}

bool getState() {
//  Serial.print("x = " + String(digitalRead(relayPin)));
//  Serial.print(", c = " + String(relayPinUpSwitchesOn));
//  Serial.println(" => " + String(digitalRead(relayPin) ^ !relayPinUpSwitchesOn));
  return (digitalRead(relayPin) ^ !relayPinUpSwitchesOn);
}
