#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Adafruit_Sensor.h>
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

//#define WIFI_SSID "Lenovo K6 NOTE"
//#define WIFI_PASSWORD "12345678"



// Config DHT
#define DHTPIN D3
#define DHTTYPE DHT11
//#define UpperThreshold 550
//#define LowerThreshold 500
const int sensor1 = D1;
//const int pirinput2 = D2;
const int ledpin = D5;
const int ledpin2 = D6;
const int ledpin3 = D7;
//const int ledpin4 = D8;
const int pirinput  = D4;
const int Alarm= D8;
int count = 0;  // นับเวลา นิ่ง
int statusSw1 = 0;

const int heartsensor = A0;

int pirValue = 0;
String textPir = "";
String textStatus = "";

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);
  pinMode(pirinput, INPUT);
  pinMode(sensor1, INPUT);
  //pinMode(sensor2, INPUT);
  pinMode(Alarm, OUTPUT);
  pinMode(heartsensor, INPUT);
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

  digitalWrite(Alarm,HIGH);
  delay(2000);
  digitalWrite(Alarm,LOW);
}



void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int i = 33;
  int led_status;
  

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
  
  pirValue = digitalRead(pirinput);
  if(pirValue == 1){
    Serial.println("Motion pir OK!!!!");
    digitalWrite(ledpin2, HIGH);
    textPir = "ในห้องนอน";
  }else if(pirValue == 0){
    Serial.println("Motion don't Ok !!");
    digitalWrite(ledpin2, LOW);
    textPir = "อยู่ภายในบ้าน";
  }  
  
  Serial.print("temperature is ");
  Serial.print(t);
  Serial.print(" *C ");
   
  if(i<=t){
    Serial.println("temperature is over");
    digitalWrite(ledpin ,HIGH);
    delay(2000);
    
  }else{
    digitalWrite(ledpin ,LOW);
    Serial.println("temperature is OK");
    delay(1000);
  }


  Firebase.setFloat("temperature", t);
  if (Firebase.failed()) {
      Serial.print("pushing /temperature failed:");
      Serial.println(Firebase.error());  
      digitalWrite(ledpin,HIGH);
      return;
  }
  Serial.print("pushed: /temperature/");
  //Serial.println(name);

  // append a new value to /temperature

  Firebase.setInt("TempStatus", led_status);
  if (Firebase.failed()) {
      Serial.print("pushing /tempStatus failed:");
      Serial.println(Firebase.error());  
      
      return;
  }
  Serial.print("pushed: /status_led/");
  //Serial.println(name);

  
  Firebase.setString("PIRSensor", textPir);
  if (Firebase.failed()) {
      Serial.print("pushing /pirsensor failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  
  int SW01 = digitalRead(sensor1);
  //int sensor2 = digitalRead(SW02);
  if(SW01 == LOW)
  {
    if(statusSw1 == HIGH)
    {   
      count = 0;
      statusSw1 = LOW;
      Serial.println("ปกติ");
      textStatus = "ปกติ";
    }
//    else{
//      count++;  
//    }
   digitalWrite(ledpin2,LOW);//เหลือง
   digitalWrite(ledpin3,HIGH); // เขียว

  }else
  {
    if(statusSw1==LOW)
    {   
      count=0;
      statusSw1=HIGH;
      Serial.println("ล้ม");
      textStatus = "หกล้ม";
    }
//    else
//    {
//      count++;  
//    }
    digitalWrite(ledpin2,HIGH);
    digitalWrite(ledpin3,LOW);
  } 
   Firebase.setString("Status", textStatus);
    if (Firebase.failed()) {
      Serial.print("pushing /Status failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Firebase.setInt("intStatus", statusSw1);
    if (Firebase.failed()) {
      Serial.print("pushing /Status failed:");
      Serial.println(Firebase.error());  
      return;
  }
  int rate = 513;
  int rateBPM = analogRead(A0);
  if(rateBPM >= rate){
    rateBPM = rateBPM/10;
    digitalWrite(ledpin, HIGH);
    delay(1000);
    digitalWrite(ledpin, LOW);
    Serial.print(rateBPM);
    Serial.println(" BPM");
  }

  Firebase.setInt("BPM",rateBPM);
  if (Firebase.failed()) {
      Serial.print("pushing /BPM failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  delay(5000);  
}
