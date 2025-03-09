#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = D7;
const int LOADCELL_SCK_PIN = D8;  

LiquidCrystal_I2C lcd(0x27, 16, 2);
HX711 scale;

void setup() {
  Serial.begin(115200);
  Serial.println("Pastikan Tidak Ada Beban");
  lcd.begin();
  lcd.backlight();
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-4.08);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(50);				        // reset the scale to 0
  Serial.println("Silahkan Untuk Menimbang");
}

void loop() {
  Serial.print("Berat");
  float berat= scale.get_units(25);
  if(berat<=0.1)
  {
    berat=0.0;
  }
  Serial.println(berat,1);
  if(berat<1000)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SILAHKAN TIMBANG");
  lcd.setCursor(0, 1);
  lcd.print("Berat= ");
  lcd.print(berat,1);
  lcd.print(" g");
  }
  if(berat>=1000)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SILAHKAN TIMBANG");
  float hasil=berat/1000;
  lcd.setCursor(0, 1);
  lcd.print("Berat= ");
  lcd.print(hasil);
  lcd.print(" kg");
  }
  scale.power_down();
  delay(2000);
  scale.power_up();
}
