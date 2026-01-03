volatile bool buttonEvent = false;
volatile bool tiltEvent = false;

const int shockPin = 4;
const int pirPin = 5;
const int clkPin = 6;
const int dtPin = 7;

bool lastShockState = LOW;
bool lastPirState = LOW;
int lastClkState;

void buttonISR() {
  buttonEvent = true;
}

void tiltISR() {
  tiltEvent = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(shockPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);

  lastClkState = digitalRead(clkPin);

  attachInterrupt(digitalPinToInterrupt(2), buttonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(3), tiltISR, CHANGE);
}

void loop() {
  if (buttonEvent) {
    buttonEvent = false;
    Serial.println("EVENT BUTTON");
  }

  if (tiltEvent) {
    tiltEvent = false;
    Serial.println("EVENT TILT");
  }

  bool shockState = digitalRead(shockPin);
  if (shockState == HIGH && lastShockState == LOW) {
    Serial.println("EVENT SHOCK");
  }
  lastShockState = shockState;

  bool pirState = digitalRead(pirPin);
  if (pirState == HIGH && lastPirState == LOW) {
    Serial.println("EVENT MOTION");
  }
  lastPirState = pirState;

  int clkState = digitalRead(clkPin);
  if (clkState != lastClkState) {
    if (digitalRead(dtPin) != clkState) {
      Serial.println("EVENT ROTARY CW");
    } else {
      Serial.println("EVENT ROTARY CCW");
    }
  }
  lastClkState = clkState;
}
