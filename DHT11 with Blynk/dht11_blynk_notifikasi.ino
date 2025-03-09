#define BLYNK_TEMPLATE_ID "TMPL6_tR7lhmD"
#define BLYNK_TEMPLATE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "c4jkjdHJ1Ep6eX91j1HWVGRggiaAa-cn"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 

#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "*********";          // nama wifi
char pass[] = "*********";          // password wifi

#define DHTPIN D4          // Mention the digital pin where you connected 
#define DHTTYPE DHT11     // DHT 11  
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;



void setup(){
   Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  dht.begin();
  timer.setInterval(2500L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  
  Serial.print("Suhu : ");
  Serial.print(t);
  Serial.print("|| Kelembapan : ");
  Serial.println(h);


  if(t > 30){
    //Blynk.email("isamahfudi08@gmail.com", "Alert", "Temperature over 30C!");
    Blynk.logEvent("notifikasi","Suhu diatas 30 Derajat celcius");
  }
}
