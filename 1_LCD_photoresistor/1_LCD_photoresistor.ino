#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

int lightPin = A2;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.

void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  lcd.setCursor(0,0); //First line
  
}

void loop(){
  Serial.println(analogRead(lightPin));
  if (analogRead(lightPin) > 450){
    lcd.print("Its nightime :)");
    delay(1500);
    lcd.clear();
    delay(100);
  }

  else{
    lcd.print("Its daytime :)");
    delay(1500);
    lcd.clear();
    delay(100);
  }
  
  delay(20);
  
}
