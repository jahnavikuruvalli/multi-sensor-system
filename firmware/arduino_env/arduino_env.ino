#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

unsigned long lastSample = 0;
const unsigned long SAMPLE_INTERVAL = 2000;

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  unsigned long now = millis();

  if (now - lastSample >= SAMPLE_INTERVAL) {
    lastSample = now;

    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    int ldr = analogRead(A0);
    int gas = analogRead(A1);
    int sound = analogRead(A2);
    int water = analogRead(A3);

    Serial.print("NODE1, ENV,");
    Serial.print(now);
    Serial.print(",");
    Serial.print(temp);
    Serial.print(",");
    Serial.print(hum);
    Serial.print(",");
    Serial.print(ldr);
    Serial.print(",");
    Serial.print(gas);
    Serial.print(",");
    Serial.print(sound);
    Serial.print(",");
    Serial.println(water);
  }

  unsigned long lastHeartbeat = 0;

  if(now - lastHeartbeat >= 5000){
    lastHeartbeat = now;
    Serial.println("NODE1,HEARTBEAT");
  }

}
