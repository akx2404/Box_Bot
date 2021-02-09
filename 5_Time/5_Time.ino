#include <Time.h>
#include <TimeLib.h>

#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();  
}

void loop()
{
  digitalClockDisplay();
  delay(990);
  lcd.clear();
  delay(10);
}
void digitalClockDisplay()
{
  lcd.print(hour());
  printDigits(minute());
  printDigits(second());
  
}
void printDigits(int digits)
{
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);  
}
