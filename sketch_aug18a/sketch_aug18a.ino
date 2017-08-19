#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "Nat-Ministrator"
#define WIFI_PASSWORD "Nat15099"
#define FIREBASE_HOST "wio-link-d6bXX.firebaseio.com"
#define FIREBASE_AUTH "qUohEtHyvCcOzgxq95ZheaVsaMePi2P5FDd8XXXX"

const int ledPin = 14;

void setup() {
  Serial.begin(9600);
  Serial.println(WiFi.localIP());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  pinMode(ledPin, OUTPUT);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("LED", 0);
}

void loop() {
  digitalWrite(ledPin, Firebase.getInt("LED"));
  delay(500);
}
