//IntelliAir code 


#include <LiquidCrystal.h>
#include <MQ135.h>
//variables and constants 


LiquidCrystal lcd(7, 8, 24, 26, 28, 30);

const int PIN_MQ135 = 15;
const int button = 10;
float temp = 21.0; 
float humidity = 50.0; 
//const int tach = 2;
const int fanPin = 3; 
int speed = 0;
int newSpeed = 1; 
bool speedOverride = 0;

MQ135 mq135_sensor(PIN_MQ135, 58.00);
 

int mapToAQI(float ppm) {
  ppm = constrain(ppm, 150, 2500);
  float aqi = map(ppm, 150, 2500, 0, 500);
  return aqi; 
}

int fanSpeed(int aqi) {
  int speed = 0;
  if (aqi <= 50) {
    speed = 162;
  } else if (aqi > 51 && aqi <= 100) {
    speed = 190;
  } else if (aqi > 101 && aqi <= 150) {
    speed = 220; 
  } else if (aqi > 150) {
    speed = 255;
  }
  return speed;
}


void setup() {
  
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(fanPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("\nEnter value from 0-255: \n");

}

void loop() {

  int state = digitalRead(button);
  Serial.println("switch is: ");
  Serial.println(state);
  if (state == 1) {
    speed = 0; 
  }
  //reads ppm from MQ135 and converts it to an approximation of AQI 
  float ppm = mq135_sensor.getCorrectedPPM(temp, humidity); 
  int aqi = mapToAQI(ppm); 

  newSpeed = Serial.parseInt();

  // reads input of the MQ135 sensor and displays it to the lcd
  lcd.setCursor(0,0);
  Serial.println(aqi);
  lcd.print("AQI: ");
  if (aqi > 99) {
    lcd.print(aqi);

  } else {
    lcd.print(aqi);
    lcd.print(" ");

  }
  lcd.setCursor(0, 0);




    // handles the input of the fan speed 
    /*if (Serial.available() > 0) {
    
      

      Serial.println("Fan speed is now: ");

      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("Fan speed: ");
      lcd.print(newSpeed);
      speed = newSpeed;
      Serial.println(speed);

    }*/

  //changes the fan speed, if there is a new input detected 

  if (state == 0) {
    speed = fanSpeed(aqi);
    
  }
  analogWrite(fanPin, speed); 
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Fan speed: ");
  lcd.print(speed);


  while(Serial.available() > 0) {
    Serial.read();  
  }



}
