#include <Arduino.h>
#include "DHT.h"

// 🔌 Pin Definitions
#define DHTPIN 4
#define DHTTYPE DHT22

#define LED 19
#define BUZZER 18
#define PIR 5
#define GAS 34   // potentiometer (gas simulation)

// 🌡️ Initialize DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR, INPUT);

  dht.begin();
}

void loop() {
  // 📊 Read Sensors
  float temp = dht.readTemperature();
  int motion = digitalRead(PIR);
  int gas = analogRead(GAS);

  // 🖥️ Print values
  Serial.println("----- SENSOR DATA -----");
  Serial.print("Temperature: ");
  Serial.println(temp);

  Serial.print("Motion: ");
  Serial.println(motion);

  Serial.print("Gas Level: ");
  Serial.println(gas);
  Serial.println("-----------------------");

  // 🚨 Alert Logic
  if (temp > 50 || motion == 1 || gas > 300) {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    Serial.println("⚠️ ALERT TRIGGERED!");
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER, LOW);
  }

  delay(1000); // 1 second delay
}