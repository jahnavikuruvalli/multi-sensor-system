#define PIR_PIN 2
#define SHOCK_PIN 3
#define TRIG_PIN 6
#define ECHO_PIN 7
#define LASER_PIN 8

#define FLAME_PIN A0
#define IR_PIN A1

volatile bool pirEvent = false;
volatile bool shockEvent = false;

unsigned long lastUltraCheck = 0;
unsigned long lastAnalogCheck = 0;

void pirISR() {
  pirEvent = true;
}

void shockISR() {
  shockEvent = true;
}

long readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  long dist = duration * 0.034 / 2;
  return dist;
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(SHOCK_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LASER_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIR_PIN), pirISR, RISING);
  attachInterrupt(digitalPinToInterrupt(SHOCK_PIN), shockISR, RISING);
}

void loop() {
  unsigned long now = millis();

  // ---- INTERRUPT EVENTS ----
  if (pirEvent) {
    pirEvent = false;
    Serial.print("NODE2,EVENT,MED,MOTION,");
    Serial.println(now);
  }

  if (shockEvent) {
    shockEvent = false;
    Serial.print("NODE2,EVENT,HIGH,SHOCK,");
    Serial.println(now);
  }

  // ---- ANALOG EVENTS ----
  if (now - lastAnalogCheck > 200) {
    lastAnalogCheck = now;

    int flame = analogRead(FLAME_PIN);
    int ir = analogRead(IR_PIN);
    int laser = digitalRead(LASER_PIN);

    if (flame < 400) {
      Serial.print("NODE2,EVENT,HIGH,FLAME,");
      Serial.println(now);
    }

    if (ir < 300) {
      Serial.print("NODE2,EVENT,LOW,OBSTACLE,");
      Serial.println(now);
    }

    if (laser == LOW) {
      Serial.print("NODE2,EVENT,LOW,LASER_BREAK,");
      Serial.println(now);
    }
  }

  // ---- ULTRASONIC EVENT ----
  if (now - lastUltraCheck > 500) {
    lastUltraCheck = now;

    long d = readDistance();
    if (d > 0 && d < 30) {
      Serial.print("NODE2,EVENT,MED,DISTANCE,");
      Serial.println(now);
    }
  }
}
