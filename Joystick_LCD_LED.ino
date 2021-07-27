/*
 Pins:
 Joystick-
   SW: Arduino UNO pin 13
   VRX: Arduino UNO pin A1
   VRY: Arduino UNO pin A0
   +5V: Aruino UNO 5V
   GND: Ardunio UNO GND
 LCD screen
   VSS: Ardunio UNO GND
   VDD: Aruino UNO 5V
   RS: to digital pin 12
   VO: Potentiometer
   RS: Arduino UNO pin 2
   RW: Arduini UNO GND
   EN: Arduino UNO pin 11
   
   D4: Arduino UNO pin 4
   D5: Arduino UNO pin 5
   D6: Arduino UNO pin 6
   D7: Arduino UNO pin 7

   A: Arduino UNO 5V through 220ohm resistor
   K: Arduino UNO GND
 Potentiometer:
   5V: Arduino UNO 5v
   GND: Arduino UNO GND
 RGB LED:
   R: Arduino UNO pin 11 through 330ohm resistor
   G: Arduino UNO pin 10 through 330ohm resistor
   B: Arduino UNO pin 9 through 330ohm resistor
   GND: Arduino UNO GND
 */

#include <LiquidCrystal.h>
LiquidCrystal lcd (2, 3, 4, 5, 6, 7);
const int redPin= 11;
const int greenPin= 10;
const int bluePin= 9;



const int jxPin = 0;
const int jyPin = 1;
const int swPin = 13;

int swState = 0;
int joyX;
int joyY;
int prevjoyY = 511;

int ledState = 0;
int r = 0, g = 0, b = 0;

String rgbVal = "";


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(swPin, INPUT_PULLUP);

  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
  joyX = analogRead(jxPin); 
  joyY = analogRead(jyPin);
  swState = digitalRead(swPin);

  
  Serial.println(joyY);
  Serial.println(prevjoyY);
  if (joyY > 600 && prevjoyY < 600){
    ledState += 1;
  }
  else if(joyY < 400 && prevjoyY > 400){
    ledState += 2;
  }
  if(ledState % 3 == 0 ){
    if(joyX > 600 && r < 255){
      r += 5;
    }else if( joyX < 400 && r > 0){
      r -= 5;
    }
  }
  if(ledState % 3 == 1 ){
    if(joyX > 600 && g < 255){
      g += 5;
    }else if( joyX < 400 && g > 0){
      g -= 5;
    }
  }
  if(ledState % 3 == 2 ){
    if(joyX > 600 && b < 255){
      b += 5;
    }else if( joyX < 400 && b > 0){
      b -= 5;
    }
  }
  if(swState == 0){
    Serial.print("Switch State: ");
    Serial.print(swState);
    Serial.print("\n");
    r = 0;
    g = 0;
    b = 0;
    ledState = 0;
    lcd.clear();
  }

  prevjoyY = joyY;
  RGB_color(r, g, b);
  if(r < 100 || g < 100|| b < 100){
    lcd.clear();
  }
  lcd.setCursor(0,0);
  lcd.print("RGB:");
  
  lcd.setCursor(0, 1);
  rgbVal = String("(" + String(r) + "," + String(g) + "," + String(b) + ")");
  lcd.print(rgbVal);
  Serial.print("\n");
  
  delay(300);
  
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(redPin, red_light_value);
  analogWrite(greenPin, green_light_value);
  analogWrite(bluePin, blue_light_value);
}
