#include <LiquidCrystal.h>
#include <MQ135.h>

LiquidCrystal lcd(7, 8, 24, 26, 28, 30);

const int tach = 2;
const int fanPin = 3; 

int speed = 0; 
int newSpeed = 1; 

void setup() {
  lcd.begin(16, 2);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("\nEnter value from 0-255: \n");


}

void loop() {
  lcd.setCursor(0, 0);
  
  newSpeed = Serial.parseInt();
  if (Serial.available() > 0) {
  

    Serial.println("Fan speed is now: ");

    lcd.clear();
    lcd.print(newSpeed);
    speed = newSpeed;
    Serial.println(speed);

  }
  

  analogWrite(fanPin, speed); 

  while(Serial.available() > 0) {
    Serial.read();  
  }

}
