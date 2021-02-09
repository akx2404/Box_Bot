#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h> 

#define touchpin A0

void setup() {
  Serial.begin(115200);

}

void loop() {
 int touch = analogRead(touchpin);
  Serial.println(touch);
  delay(1000);

}
