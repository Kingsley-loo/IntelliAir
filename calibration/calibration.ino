//Key parts of this code borrow from https://github.com/NuclearPhoenixx/MQ135/blob/master/examples/MQ135/MQ135.ino
//This is the author/maintainer of the MQ135 library, and he has provided examples on how to calibrate the sensor. 

#include <LiquidCrystal.h>
#include <MQ135.h>


LiquidCrystal lcd(7, 8, 24, 26, 28, 30);
const int PIN_MQ135 = 15;
float temperature = 21.0; 
float humidity = 50.0; 
int mapToAQI(float ppm) {
  ppm = constrain(ppm, 150, 2500);
  float aqi = map(ppm, 150, 2500, 0, 500);
  return aqi; 
}
MQ135 mq135_sensor(PIN_MQ135);
void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600); 
  lcd.setCursor(0, 1);
  lcd.print("CALIBRATION MODE");

}

void loop() {
  //code borrowed from https://github.com/NuclearPhoenixx/MQ135/blob/master/examples/MQ135/MQ135.ino
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);

  Serial.print("MQ135 RZero: ");
  Serial.print(rzero);
  Serial.print("\t Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");


  int aqi = mapToAQI(correctedPPM);

  lcd.setCursor(0,0);
  Serial.println(aqi);
  lcd.print("AQI: ");
  if (aqi > 99) {
    lcd.print(aqi);

  } else {
    lcd.print(aqi);
    lcd.print(" ");

  }

  delay(1000);
}
