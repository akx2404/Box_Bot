#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.

#define ThermistorPin A0
double Thermistor(int RawADC)
{
    double Temp;
    Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
    Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
    Temp = Temp - 273.15;            // convert from Kelvin to Celsius
    return Temp;
}

void setup(){
  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  lcd.setCursor(0,0); //First line
  
}

void loop(){

  int readVal = analogRead(ThermistorPin);
  double temp =  Thermistor(readVal);

  lcd.print("Temperature- ");
  lcd.setCursor(0,1);
  lcd.print(temp);
  lcd.print((char)223);
  lcd.print("C"); 

  delay(1500);
  lcd.clear();
  delay(500);

  
}
