
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//--------------------------------------------------------
//#define SSID          "----------" // ชื่อ Internet WiFi Router
//#define PASSWORD      "----------" // รหัสลับของ WiFi Router

#define SSID       "Thunnathorn-2.4G"
#define PASSWORD   "mcc12azy"

#define FIREBASE_HOST "https://fir-iot-2f553.firebaseio.com/"
#define FIREBASE_AUTH "cKkWWFXp5ulC98OGUx5Wzf19YljiUrcFqMJiqkMS"

#define OUTPUT_K1 D0
#define OUTPUT_K2 D1
//--------------------------------------------------------
/* ฟังกชั่น สำหรับ ESP8266 รับและส่งข้อมูลไปยัง Firebase*/
String  TD_Get_Firebase(String path );                                // สำหรับรับ
int     TD_Set_Firebase(String path, String value, bool push=false ); // สำหรับส่ง
int     TD_Push_Firebase(String path, String value ); // สำหรับส่งแบบ Pushing data
//--------------------------------------------------------

void setup() {
  Serial.begin(115200); Serial.println();
  WiFi.begin(SSID, PASSWORD);             // ทำการเชื่อมต่อ WiFi
  while(!WiFi.isConnected()) delay(400);  // รอจนกว่าจะเชื่อมต่อ WiFi ได้
  
  pinMode(OUTPUT_K1, OUTPUT);
  pinMode(OUTPUT_K2, OUTPUT);

  delay(10);
  
  // กำหนดค่าเริ่มต้นให้ output เป็น off
  digitalWrite(OUTPUT_K1, HIGH);  // Relay active LOW
  digitalWrite(OUTPUT_K2, HIGH);  // Relay active LOW
  
  Serial.println(WiFi.localIP());         // แสดงค่า IP หลังเชื่อมต่อ WiFi สำเร็จ
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
int cnt;
uint32_t timers;

void loop() {
  if( millis() -timers > 3000) {       // ทำการอ่านค่าและส่งทุกๆ 3 วินาที
    timers = millis();
    
    float t = (float)random(2000,4000)/100;  // อ่านค่า อุณหภูมิ (สมมติใช้ค่า random แทน)
    float h = (float)random(1000,9000)/100;  // อ่านค่า ความชื้น (สมมติใช้ค่า random แทน)

    checkStatus1();
    checkStatus2();

  }
}
void checkStatus1(){
    int str_status1 = Firebase.getInt("lamp/lamp1");
    int status1 = str_status1;
    if(status1 == 1){
        Serial.println("output1 high");
        digitalWrite(OUTPUT_K1,HIGH);
    }
    else if(status1 == 0){
        Serial.println("output1 low");
        digitalWrite(OUTPUT_K1,LOW);
    }
}
void checkStatus2(){
    int str_timer = Firebase.getInt("lamp/lamp2");
    int fire_db = str_timer;
    int timer = (1000*fire_db);
    if(str_timer != 0){
        Serial.println("output2 high" + timer);
        digitalWrite(OUTPUT_K2,HIGH);
        delay(timer);
        Serial.println("output1 low" + timer);
        digitalWrite(OUTPUT_K2,LOW);
    }
    else if(str_timer == 0){
        Serial.println("output1 low");
        digitalWrite(OUTPUT_K2,LOW);
    }
}
