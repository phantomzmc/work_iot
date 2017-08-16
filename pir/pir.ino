#define ledPin D2 // Red LED
#define pirPin D1 // Input for HC-SR501

int pirValue; // variable to store read PIR Value

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop() 
{
  pirValue = digitalRead(pirPin);
  digitalWrite(ledPin, pirValue);
}
