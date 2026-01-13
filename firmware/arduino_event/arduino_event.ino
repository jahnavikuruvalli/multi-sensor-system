#include <SoftwareSerial.h>

SoftwareSerial link(8,9); // RX, TX

void setup(){
  Serial.begin(9600);
  link.begin(9600);
}

void loop(){
  while(link.available()){
    Serial.write(link.read());
  }

  link.println("<EVENT:BUTTON>");
  delay(1500);
}
