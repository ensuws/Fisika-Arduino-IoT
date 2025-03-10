#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

const int lebar=128;
const int tinggi=64;
const int reset=4;
int rawvalue;
int led = 13 ;

Adafruit_SSD1306 oled(lebar,tinggi,&Wire,reset);

char ADCSHOW[5];//initializing a character of size 5 for showing the ADC result

const unsigned char karakter [] PROGMEM = {
  // 'IKIP PGRI Pontianak, 128x64px
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x98, 0x19, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x60, 0x06, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0x80, 0x01, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc, 0x00, 0x00, 0x67, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x90, 0x00, 0x00, 0x09, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x40, 0x00, 0x00, 0x02, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x80, 0x00, 0x00, 0x01, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe4, 0x00, 0x00, 0x00, 0x00, 0x27, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x13, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x09, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0x60, 0x00, 0x00, 0x00, 0x00, 0x04, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x40, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfd, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfa, 0x00, 0x02, 0x00, 0x00, 0x40, 0x00, 0x5f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf4, 0x00, 0x02, 0x00, 0x00, 0xc0, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xe8, 0x00, 0x03, 0x00, 0x00, 0xc8, 0x00, 0x17, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xd0, 0x00, 0x13, 0x07, 0xc1, 0xc8, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0x13, 0x03, 0xc1, 0xd8, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x60, 0x00, 0x1b, 0x03, 0x80, 0x98, 0x00, 0x06, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x40, 0x00, 0x1a, 0x07, 0xa0, 0x39, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x40, 0x00, 0x9c, 0x13, 0x88, 0x3b, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0xd8, 0x01, 0x84, 0x33, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0xd8, 0x41, 0x80, 0x16, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0xe8, 0x01, 0x80, 0x1e, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0x70, 0x9f, 0xf8, 0x1e, 0x40, 0x05, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa0, 0x02, 0x70, 0x1d, 0xb9, 0x1c, 0xc0, 0x05, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa0, 0x03, 0x30, 0x09, 0x91, 0x1c, 0xc0, 0x05, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa0, 0x03, 0xb2, 0xc1, 0x21, 0x19, 0x80, 0x05, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xa0, 0x01, 0xd0, 0xa1, 0x04, 0x13, 0x80, 0x07, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xe8, 0x00, 0x00, 0x0f, 0x20, 0x07, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xc0, 0x04, 0xf8, 0x7f, 0xfc, 0x1f, 0x40, 0x03, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xc0, 0x06, 0xf8, 0x3f, 0xfc, 0x3e, 0xc0, 0x0b, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xd0, 0x03, 0xbc, 0x10, 0x08, 0x3d, 0xc0, 0x0b, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xd0, 0x03, 0xde, 0x04, 0x20, 0x7b, 0x80, 0x0b, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xd0, 0x01, 0xf6, 0x00, 0x00, 0xdf, 0x80, 0x0b, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf0, 0x01, 0xff, 0x03, 0xc1, 0xff, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0xff, 0x78, 0x1d, 0xfe, 0x00, 0x17, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xe8, 0x00, 0x7f, 0xfe, 0x7f, 0xfc, 0x00, 0x17, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xe8, 0x00, 0x1f, 0xf2, 0xcf, 0xf0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x06, 0xaa, 0xce, 0xe0, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf4, 0x00, 0x06, 0x32, 0xcd, 0xc0, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x03, 0xfe, 0xf5, 0xc0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfa, 0x00, 0x03, 0xef, 0xff, 0xc0, 0x00, 0x5f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x02, 0x6e, 0xbd, 0x40, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xbf, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x7f, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0x40, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0x40, 0x00, 0x00, 0x00, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x17, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x17, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x00, 0x00, 0x00, 0x00, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xf8, 0x00, 0x00, 0x1f, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0x80, 0x01, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void setup() {
  Serial.begin(9600);
  pinMode (led, OUTPUT);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!oled.begin(SSD1306_SWITCHCAPVCC,0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  oled.clearDisplay();
  oled.drawBitmap(0, 0,karakter, 128, 64, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  oled.display();
  delay(3000);
  oled.clearDisplay();
  oled.setCursor(20,0);  
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.println("Magnetic");
  oled.setCursor(35,22);
  oled.setTextSize(2);
  oled.print("Field");
  oled.setCursor(35,44);
  oled.setTextSize(2);
  oled.print("Meter");
  oled.display();
  delay(3000);
}

void loop() {
  rawvalue = analogRead(A0);
  Serial.println(rawvalue);

  if (rawvalue > 575  ||  rawvalue < 565 )
  {
    digitalWrite (led, HIGH);
  }
  else
  {
    digitalWrite (led, LOW);
  }

  oled.clearDisplay();
  oled.setCursor(35,5);  
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.println("Gaus:");

  String ADCVALUE = String((analogRead(A0)-569)/0.376);

 /* Now since the default reference if 5V and resolution is 10bit so for every 5/1024 = 5mV, we get one increment is count, The sensor provides increment voltage of 1.3mV for every 1Gauss increment if field. So we need to divide ADC value by 3.76 for getting the gauss value, now the 0 gauss output of sensor is 2.5V so we need to subtract that first. To hold a 0V read at 0Gauss field. */
 // Convert the reading to a char array

  ADCVALUE.toCharArray(ADCSHOW, 5);

  oled.setCursor(20,30);
  oled.setTextSize(4);
//  oled.print(ADCSHOW);
  oled.print(rawvalue);
  oled.display();
  delay(100);
}
