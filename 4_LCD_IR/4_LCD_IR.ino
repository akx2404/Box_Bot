#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
const int IRsens=11;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.

void setup(){
  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  pinMode(IRsens,INPUT);
  lcd.clear();
}

void loop() {
  int ss=digitalRead(IRsens);
  
  if(ss==HIGH){
    delay(500);
  }
  else{
    lcd.print("gotcha!");
    delay(500);
  }

  delay(100);
  lcd.clear();

}
