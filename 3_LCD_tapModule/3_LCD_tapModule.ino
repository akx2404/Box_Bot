#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.

int Shock = 10;
int val;

void setup(){
  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  lcd.setCursor(0,0); //First line
  lcd.print("I2C LCD");
  lcd.setCursor(0,1); //Second line
  lcd.print("*Akshad*");
  pinMode(Shock, INPUT);
}

void loop(){
  val = digitalRead(Shock) ; // Reads Digital Pin of sensor.
  if (val == 0) // When the shock sensor detects a signal, LED flashes
  {
    lcd.write("accident!");
    delay(1000);
  }
  lcd.clear();
}
