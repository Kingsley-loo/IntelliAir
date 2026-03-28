//IntelliAir code 


#include <LiquidCrystal.h>

//variables and constants 
LiquidCrystal lcd(7, 8, 24, 26, 28, 30);

const int mq135 = 0;
const int tach = 2;
const int fanPin = 3; 

int speed = 0; 
int newSpeed = 1; 
int sensorValue; 
void setup() {
  lcd.begin(16, 2);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("\nEnter value from 0-255: \n");


}

void loop() {
  lcd.setCursor(0, 0);


  
  newSpeed = Serial.parseInt();

  // reads input of the MQ135 sensor and displays it to the lcd
  int sensorValue = analogRead(mq135); 
  Serial.println(sensorValue);
  lcd.print("air quality: ");
  if (sensorValue > 99) {
    lcd.print(sensorValue);

  } else {
    lcd.print(sensorValue);
    lcd.print(" ");

  }
  lcd.print(sensorValue);


  // handles the input of the fan speed 

  if (Serial.available() > 0) {
  
    

    Serial.println("Fan speed is now: ");

    lcd.setCursor(1, 0);
    lcd.print(newSpeed);
    speed = newSpeed;
    Serial.println(speed);

  }
  
  //changes the fan speed, if there is a new input detected 
  analogWrite(fanPin, speed); 

  while(Serial.available() > 0) {
    Serial.read();  
  }


}
