#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define LDR_PIN A0
#define SOUND_PIN A1
#define FLAME_PIN A2
#define DHT_PIN A3
#define DHT_TYPE DHT11
#define DS18B20_PIN 2
#define LED 13

unsigned long lastSample = 0;
unsigned long lastBeat = 0;

DHT dht(DHT_PIN, DHT_TYPE);
OneWire oneWire(DS18B20_PIN);
DallasTemperature ds(&oneWire);

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  dht.begin();
  ds.begin();
}

void loop() {
  unsigned long now = millis();

  if (now - lastBeat >= 500) {
    lastBeat = now;
    digitalWrite(LED, !digitalRead(LED));
  }

  if (now - lastSample >= 1000) {
    lastSample = now;
    sample();
  }
}

void sample() {
  ds.requestTemperatures();

  Serial.print("DATA ");
  Serial.print(analogRead(LDR_PIN));
  Serial.print(" ");
  Serial.print(analogRead(SOUND_PIN));
  Serial.print(" ");
  Serial.print(analogRead(FLAME_PIN));
  Serial.print(" ");
  Serial.print(dht.readHumidity());
  Serial.print(" ");
  Serial.print(dht.readTemperature());
  Serial.print(" ");
  Serial.println(ds.getTempCByIndex(0));
}
