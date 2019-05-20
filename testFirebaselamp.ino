
#include <ESP8266WiFi.h>

//--------------------------------------------------------
#define SSID          "----------" // ชื่อ Internet WiFi Router
#define PASSWORD      "----------" // รหัสลับของ WiFi Router

#define FIREBASE_HOST "https://fir-iot-2f553.firebaseio.com/"
#define FIREBASE_AUTH "cKkWWFXp5ulC98OGUx5Wzf19YljiUrcFqMJiqkMS"
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

    led1();
    led2();

  }
  void led1(){
    string str_status1 = Firebase.getInt("lamp").child("lamp1");
    int status1 = str_status1.ToInt();
    if(status1 == 1){
        digital.Write(LED1,HIGH);
    }
    else if(status1 == 0){
        digital.Write(LED1,LOW);
    }
  }
  void led2(){
    string str_timer = Firebase.getInt("lamp").child("lamp2");
    int fire_db = str_timer.ToInt();
    int timer = (1000*fire_db);
    if(str_timer != 0){
        digital.Write(led2,HIGH);
        delay(timer);
        digital.Write(led2,LOW);
    }
    else if(str_timer == 0){
        digital.Write(led2,LOW);
    }
  }
}