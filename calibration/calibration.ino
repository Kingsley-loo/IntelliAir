
#include <LiquidCrystal.h>
#include <MQ135.h>


LiquidCrystal lcd(7, 8, 24, 26, 28, 30);
const int PIN_MQ135 = 15;
float temp = 21.0; 
float humidity =  50.0; 
MQ135 mq135_sensor(PIN_MQ135);


void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600); 
  lcd.setCursor(0, 1);
  lcd.print("CALIBRATION MODE");
  Serial.print("MQ135 Calibration");

}

void loop() {
  //run calibrations to get RZero, use stable RZero value when running air purifier
  float correctedRZero = mq135_sensor.getCorrectedRZero(temp, humidity);
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temp, humidity);

  Serial.println();
  Serial.print("Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println();

  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.print("ppm: ");
  lcd.print(ppm);

  delay(1000);
}
