const int pin_led1 = D1;
const int pin_led2 = D2;
const int input_data = D3;

int buttonChage = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_led1,OUTPUT);
  pinMode(pin_led2, OUTPUT);
  pinMode(input_data,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonChage = digitalRead(input_data);
  if(buttonChage == HIGH){
    digitalWrite(pin_led1, HIGH);
    digitalWrite(pin_led2, LOW);
    
  }else
    digitalWrite(pin_led1, LOW);
    digitalWrite(pin_led2, HIGH);
  

}
