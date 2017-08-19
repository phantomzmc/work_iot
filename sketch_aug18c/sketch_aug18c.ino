#include <ESP8266WiFi.h>

const char* ssid     = "IThunnathorn";

const char* password = "mcc12azy";

void setup() {

  Serial.begin(115200);

  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();

  Serial.println();

  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

   delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");  

  Serial.print("IP address: ");

  Serial.println(WiFi.localIP());

 

  Serial.print("MAC address: ");

  Serial.println(WiFi.macAddress());

}

void loop() {

  delay(100);

}
