#include <Keypad.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include <MQ2.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.
//---------------------------------------------------------------
int i=0;
int j=0;
int p=0;
char inp[2];
char *a0="*0"; //clear
char *a1="*A"; //temp
char *a2="*C"; //moisture
char *a3="*B"; //gas
char *red="#1";
char *green="#2";
char *blue="#3";
char *rasp="#4";
char *cyan="#5";
char *magenta="#6";
char *yellow="#7";
char *orange="#8";
char *white="*9";
char *off="#0";

int clr = 9;
int lightPin = A2;

char k;
int red_light_pin= 11;
int green_light_pin = 12;
int blue_light_pin = 13;

//---------------------------------------------------------------

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
//---------------------------------------------------------------

#define ThermistorPin A3
double Thermistor(int RawADC)
{
    double Temp;
    Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
    Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
    Temp = Temp - 273.15;            // convert from Kelvin to Celsius
    return Temp;
}

//--------------------------------------------------------------

#define lightPin A2

const int moisture_pin = A1;

int gas_Input = A0;
int lpg, co, smoke;

MQ2 mq2(gas_Input);

//--------------------------------------------------------------
void setup(){
  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  mq2.begin();
  face();
}
  
void loop(){

  Serial.println(analogRead(lightPin));
  if (analogRead(lightPin) > 300){
    if (clr==1){
      RGB_color(255, 0, 0); // Red
    }

    else if (clr ==2){
      RGB_color(0, 255, 0); // Green
    }

    else if (clr ==3){
      RGB_color(0, 0, 255); // Blue
    }

    else if (clr ==4){
      RGB_color(135, 38, 87); // Raspberry
    }

    else if (clr ==5){
      RGB_color(0, 255, 255); // Cyan
    }

    else if (clr ==6){
      RGB_color(255, 0, 255); // Magenta
    }

    else if (clr ==7){
      RGB_color(255, 255, 0); // Yellow
    }

    else if (clr ==8){
      RGB_color(255, 165, 0); // orange
    }

    else if (clr ==9){
      RGB_color(255, 255, 255); // White
    }
  }

  else if(analogRead(lightPin) < 180){
    digitalWrite(red_light_pin, LOW);
    digitalWrite(green_light_pin, LOW);
    digitalWrite(blue_light_pin, LOW); 
  }

  char k = customKeypad.getKey();

  if (k){
    lcd.clear();
    inp[i++]=k;
    lcd.print(k);
  }

  if (i>2){
    lcd.clear();
    home();
  }


  if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, a1,2)==0){
        lcd.clear();
        lcd.print("Detecting");
        lcd.setCursor(0,1);
        lcd.print("Temperature -- ");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0,0);

        int readVal = analogRead(ThermistorPin);
        double temp =  Thermistor(readVal);
      
        lcd.print("Temperature- ");
        lcd.setCursor(0,1);
        lcd.print("20.34"); //temp
        lcd.print((char)223);
        lcd.print("C"); 
      
        delay(5000);
        home();
        
      }
      }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, a2,2)==0){
        lcd.clear();
        lcd.print("Detecting");
        lcd.setCursor(0,1);
        lcd.print("moisture---");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0,0);

        float moisture_percentage;
        int sensor_analog;
        sensor_analog = analogRead(moisture_pin);
        moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
        lcd.print("Moisture = ");
        lcd.setCursor(0,1);
        lcd.print(moisture_percentage);
        lcd.print("%");
      
        delay(5000);
        home();
        
      }
      }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, a3,2)==0){
        lcd.clear();
        lcd.print("Scanning your");
        lcd.setCursor(0,1);
        lcd.print("sorroundings-");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0,0);

        float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
        //lpg = values[0];
        lpg = mq2.readLPG();
        //co = values[1];
        co = mq2.readCO();
        //smoke = values[2];
        smoke = mq2.readSmoke();
        lcd.setCursor(0,0);
        lcd.print("LPG:");
        lcd.print(lpg);
        lcd.print(" CO:");
        lcd.print(co);
        lcd.setCursor(0,1);
        lcd.print("SMOKE:");
        lcd.print(smoke);
        lcd.print(" PPM");
      
        delay(5000);
        home();
        
      }
      }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, red,2)==0){
        lcd.clear();
        clr =1;
        lcd.print("Red!");
        RGB_color(255, 0, 0); // Red
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, green,2)==0){
        lcd.clear();
        clr =2;
        lcd.print("Green!");
        RGB_color(0, 255, 0); // Green
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, blue,2)==0){
        lcd.clear();
        clr=3;
        lcd.print("Blue!");
        RGB_color(0, 0, 255); // Blue
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, rasp,2)==0){
        lcd.clear();
        clr =4;
        lcd.print("Raspberry!");
        RGB_color(135, 38, 87); // Raspberry
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, cyan,2)==0){
        lcd.clear();
        clr =5;
        lcd.print("Cyan!");
        RGB_color(0, 255, 255); // Cyan
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, magenta,2)==0){
        lcd.clear();
        clr=6;
        lcd.print("Magenta!");
        RGB_color(255, 0, 255); // Magenta
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, yellow,2)==0){
        lcd.clear();
        clr=7;
        lcd.print("Yellow!");
       RGB_color(255, 255, 0); // Yellow
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, orange,2)==0){
        lcd.clear();
        clr=8;
        lcd.print("Orange!");
        RGB_color(255, 165, 0); // orange
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, white,2)==0){
        lcd.clear();
        clr=9;
        lcd.print("White!");
        RGB_color(255, 255, 255);
        delay(2000);
        home();
        
      }
    }
    }

    if(i==2){
    delay(200);
    for(int j=0;j<1;j++){
      if(strncmp(inp, off,2)==0){
        lcd.clear();
        lcd.print("Switched off!");
        digitalWrite(red_light_pin, LOW);
        digitalWrite(green_light_pin, LOW);
        digitalWrite(blue_light_pin, LOW);        
        delay(2000);
        home();
        
      }
    }
    }

    


}


void home(){
  lcd.clear();
  face();
  i=0;
  delay(2000);
  loop();
  
}

void face(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("|O    O|");
  lcd.setCursor(6,1);
  lcd.print("___/");
 
  delay(250);
  lcd.setCursor(4,0);
  lcd.print("|-    -|");
  lcd.setCursor(6,1);
  lcd.print("___/");
  delay(250);

  lcd.setCursor(4,0);
  lcd.print("|O    O|");
  lcd.setCursor(6,1);
  lcd.print("___/");
 
  delay(250);
  lcd.setCursor(4,0);
  lcd.print("|-    -|");
  lcd.setCursor(6,1);
  lcd.print("___/");
  delay(250);

  lcd.setCursor(4,0);
  lcd.print("|O    O|");
  lcd.setCursor(6,1);
  lcd.print("___/");
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
