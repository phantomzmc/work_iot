#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

// Config Firebase
#define FIREBASE_HOST "deviot-348eb.firebaseio.com"
#define FIREBASE_AUTH "tY9f5ajwULW1FWdEjSitsjAKvZUHZZs9xZb9ZLfx"

// Config connect WiFi
#define WIFI_SSID "IThunnathorn"
#define WIFI_PASSWORD "mcc12azy"

//#define WIFI_SSID "Nat-Ministrator"
//#define WIFI_PASSWORD "Nat15099"

// Config DHT
#define DHTPIN D4
#define DHTTYPE DHT11
const int ledpin = D1;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(ledpin, OUTPUT);
  
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

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = t;
  root["humidity"] = h;
  root["LEDStatus"] = led_status;

  
  // append a new value to /logDHT
  String name = Firebase.push("logDHT", root);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logDHT failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logDHT/");
  Serial.println(name);
  Serial.print("temperature is ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("humidity is ");
  Serial.print(h);
  Serial.println(" %\t ");
  if(i<=t){
    Serial.println("temperature is over");
    digitalWrite(ledpin ,HIGH);
    delay(2000);
    
  }else{
    digitalWrite(ledpin ,LOW);
    delay(1000);
  }
  delay(5000);
}
