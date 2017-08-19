#include "DHT.h"
#include <Adafruit_Sensor.h>
#define DTHPIN D3
#define DTHTYPE DHT11

DHT dht(DTHPIN,DTHTYPE);
const int ledpin = D1;

void setup(){
  pinMode(ledpin, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  delay(3000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
    Serial.print("Humidity is ");
    Serial.print(h);
    Serial.print(" %\t") ;
    Serial.print("Temperature is ");
    Serial.print(t);
    Serial.println(" *C") ;
    if(int i = 30 < t ){
      Serial.println("is Over");
      digitalWrite(ledpin ,HIGH);
      delay(1000);
      digitalWrite(ledpin ,LOW);
      delay(1000);
    }
}

