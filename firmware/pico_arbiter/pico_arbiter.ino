#define UART0_RX 1   // Node1
#define UART1_RX 5   // Node2

String bufNode1 = "";
String bufNode2 = "";

unsigned long lastNode1 = 0;
unsigned long lastNode2 = 0;

const unsigned long NODE_TIMEOUT = 6000;

void setup() {
  Serial.begin(115200);    // PC
  Serial1.begin(115200);  // Node1
  Serial2.begin(115200);  // Node2

  Serial.println("ARB,BOOT");
}

void processNode1(char c) {
  if (c == '\n') {
    unsigned long t = millis();
    Serial.print("ARB,");
    Serial.print(t);
    Serial.print(",");
    Serial.println(bufNode1);
    bufNode1 = "";
    lastNode1 = t;
  } else {
    bufNode1 += c;
  }
}

void processNode2(char c) {
  if (c == '\n') {
    unsigned long t = millis();
    Serial.print("ARB,");
    Serial.print(t);
    Serial.print(",");
    Serial.println(bufNode2);
    bufNode2 = "";
    lastNode2 = t;
  } else {
    bufNode2 += c;
  }
}

void loop() {

  // ---- READ NODE 1 ----
  while (Serial1.available()) {
    processNode1(Serial1.read());
  }

  // ---- READ NODE 2 ----
  while (Serial2.available()) {
    processNode2(Serial2.read());
  }

  unsigned long now = millis();

  // ---- HEARTBEAT MONITOR ----
  if (now - lastNode1 > NODE_TIMEOUT) {
    Serial.println("ARB,ALERT,NODE1_TIMEOUT");
    lastNode1 = now; // prevent spam
  }

  if (now - lastNode2 > NODE_TIMEOUT) {
    Serial.println("ARB,ALERT,NODE2_TIMEOUT");
    lastNode2 = now;
  }
}
