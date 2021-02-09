#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h> 

#define touchpin A0
const unsigned char buz = 2;

void setup() {
  Serial.begin(115200);
  pinMode(buz, OUTPUT);
}

void loop() {
 int touch = analogRead(touchpin);
 if (touch<300){
  tone(buz, 523) ; //DO note 523 Hz
  delay (200); 
  tone(buz, 587) ; //RE note ...
  delay (200); 
  tone(buz, 659) ; //MI note ...
  delay (200); 
  tone(buz, 783) ; //FA note ...
  delay (200); 
  tone(buz, 880) ; //SOL note ...
  delay (200); 
  tone(buz, 987) ; //LA note ...
  delay (200); 
  tone(buz, 1046) ; // SI note ...
  delay (200); 
  noTone(buz) ; //Turn off the pin attached to the tone()
  delay(1000);
 }
  
}
