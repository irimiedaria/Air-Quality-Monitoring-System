#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MQ135.h"
#include <SimpleDHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
MQ135 gasSensor(A0);

const int fanPin = 8; 
#define DHTPIN A3    
#define DHTTYPE DHT11

SimpleDHT11 dht11(DHTPIN);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(fanPin, OUTPUT); 

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Warming");
  delay(3000);
  lcd.clear();
  pinMode( DHTPIN , INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Air Quality is ");
  lcd.setCursor(0, 1);
}

void loop() {
  int air_quality = gasSensor.getPPM();
  Serial.println(air_quality);

  lcd.setCursor(15, 0);
  lcd.print(air_quality);
  lcd.print(" PPM ");

  digitalWrite(fanPin, LOW);

  lcd.setCursor(0, 1);
  if (air_quality > 2) {
    Serial.println("Turning on the fan");
    lcd.print("Polluted Air ");
    // Turn on the fan
    digitalWrite(fanPin, HIGH);
  } else {
    lcd.print("Fresh Air");
  }

  lcd.setCursor(0, 2);
  
  byte temperature = 0;
  byte humidity = 0;

  dht11.read(&temperature, &humidity, NULL);
 
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("H: ");
    lcd.print(humidity);
  
    delay(1000);
}
