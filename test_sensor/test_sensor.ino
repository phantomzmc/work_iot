int SW01 = D1;
int SW02 = D2;
int LED0 = D5;
int LED1 = D6;
int LED2 = D7;
int Alarm= D8;
int count=0;  // นับเวลา นิ่ง
int statusSw1=0;

void setup() {
  //Serial.begin

  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Alarm, OUTPUT);

  digitalWrite(Alarm,HIGH);
  delay(2000);
  digitalWrite(Alarm,LOW);
  Serial.begin(9600);

}

void recvSensor1()
{
  delay(100);
  int sensor1 = digitalRead(SW01);
  //int sensor2 = digitalRead(SW02);
  if(sensor1 == LOW)
  {
    if(statusSw1 == HIGH)
    {   
      count = 0;
      statusSw1 = LOW;
      Serial.println("ปกติ");
    }
    else{
      count++;  
    }
   digitalWrite(LED1,LOW);//เหลือง
   digitalWrite(LED2,HIGH); // เขียว

  }else
  {
    if(statusSw1==LOW)
    {   
      count=0;
      statusSw1=HIGH;
    }else
    {
      count++;  
    }
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,LOW);
  }
  
}
void checkSleep()
{
    if(count>=100){
      digitalWrite(Alarm,HIGH);
      Serial.println("ล้ม");
    }  
   else if(count <= 59){
    digitalWrite(Alarm,LOW);
      Serial.println("ปกติ");
   }
   else if(count <=60 || count >=90 ){
    Serial.println("หลับอยู่");
   } 
}
void loop() 
{
  recvSensor1();
  checkSleep();
}
