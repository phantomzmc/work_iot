#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Config Firebase
#define FIREBASE_HOST "deviot-348eb.firebaseio.com"
#define FIREBASE_AUTH "tY9f5ajwULW1FWdEjSitsjAKvZUHZZs9xZb9ZLfx"

// Config connect WiFi
//#define WIFI_SSID "IThunnathorn"
//#define WIFI_PASSWORD "mcc12azy"

#define WIFI_SSID "Nat-Ministrator"
#define WIFI_PASSWORD "Nat15099"

// Config DHT
#define DHTPIN D4
#define DHTTYPE DHT11
const int ledpin = D3;
const int ledpin2 = D2;
const int pirinput  = D1;

int pirValue = 0;

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(pirinput, INPUT);
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();

  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
}

void loop() {
  //pir sensor
  pirValue = digitalRead(pirinput);
  if(pirValue == 1){
    Serial.println("Motion pir OK!!!!");
    digitalWrite(ledpin2, HIGH);
  }else if(pirValue == 0){
    Serial.println("Motion don't Ok !!");
    digitalWrite(ledpin2, LOW);
  }
  

  // Read temp & Humidity for DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int i = 33;
  boolean led_status= 0;
  

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(3000);
    return;
  }
  if(i<=t){
    led_status = 1;
  }else{
    led_status = 0;
  }
  Firebase.setFloat("temperature", t);
  if (Firebase.failed()) {
      Serial.print("pushing /temperature failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /temperature/");
  //Serial.println(name);

  // append a new value to /temperature
  Firebase.setFloat("humidity", h);
  if (Firebase.failed()) {
      Serial.print("pushing /humidity failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /humidity/");
  //Serial.println(name);

  Firebase.setInt("LEDStastus", led_status);
  if (Firebase.failed()) {
      Serial.print("pushing /status led failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /status_led/");
  //Serial.println(name);

  
  Firebase.setFloat("PIRSensor", pirValue);
  if (Firebase.failed()) {
      Serial.print("pushing /pirsensor failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /pirsensor/");
  
  
  Serial.print("temperature is ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("humidity is ");
  Serial.print(h);
  Serial.println(" %\t ");
   
  lcd.setCursor(0,0);
  lcd.print("Temperature's");
  lcd.print(t,0);
  lcd.print("*c");
  lcd.setCursor(0,1);
  lcd.print("Humidity's");
  lcd.print(h,0);
 
  if(i<=t){
    Serial.println("temperature is over");
    digitalWrite(ledpin ,HIGH);
    delay(2000);
    
  }else{
    digitalWrite(ledpin ,LOW);
    Serial.println("temperature is OK");
    delay(1000);
  }
  delay(5000);  
}
