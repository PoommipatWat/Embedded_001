
#include <WiFi.h>
#include <MQTT.h>

#define motorPin1 23// Blue   - 28BYJ48 pin 1
#define motorPin2 22// Pink   - 28BYJ48 pin 2
#define motorPin3 21// Yellow - 28BYJ48 pin 3
#define motorPin4 19// Orange - 28BYJ48 pin 4
#define motorSpeed 4     //variable to set stepper speed
#define BUTTON 32
double begin_degree = 13.84615384615385;    //ได้ค่าจาก 360 องศา หาร 26 ช่องตัวอักษร
char inp;
double val;

const char ssid[] = "imb24";
const char pass[] = "12345678";

const char mqtt_broker[]="test.mosquitto.org";
const char mqtt_topic[]="group7/command";
int MQTT_PORT=1883;

int counter=0;

String Tex;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino_group_7")) {  // connection ID should be unique
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe(mqtt_topic);
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  Tex = payload;
  Tex.toUpperCase();
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  connect();

  pinMode(motorPin1, OUTPUT);       //ประกาศตัวแปร motorPin1 เป็น output
  pinMode(motorPin2, OUTPUT);       //ประกาศตัวแปร motorPin2 เป็น output
  pinMode(motorPin3, OUTPUT);       //ประกาศตัวแปร motorPin3 เป็น output
  pinMode(motorPin4, OUTPUT);       //ประกาศตัวแปร motorPin4 เป็น output
  pinMode(BUTTON, INPUT_PULLUP);    //ประกาศตัวแปร motorPin1 เป็น input แบบ internal pullup

}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  if (Tex != ""){
    if(Tex == "LOOP!"){
      val = 512*2;                                            //ให้หมุน 2 ครั้ง
      for (int j = 0; j < val; j++) counterclockwise();       //ลูปมอเตอร์เพื่อให้เกิดการหมุน 2 ครั้ง      
    }
    else{
      for(int k = 0; k < Tex.length(); k++){
        val = 0;    
        char Buf[50];
        Tex.toCharArray(Buf, 50);
        val = Buf[k];                      //ให้ val = inp (ASCII)
        val = val-65;                   //แปลง A จาก ASCII = 65 ถึง Z = 90 เป็นเริ่มต้น A = 0 ถึง Z = 25 
        val *= begin_degree;            //แปลงค่า A-Z เป็นหน่วยองศา 0-360 องศา
        val += (begin_degree/2);        //เนื่องจากให้ค่าเริ่มต้น เป็น 0 องศา อยู่ระหว่าง Z และ A จึงขยับค่า A-Z เป็น 13.846 - 373.846 องศา
        val = 512.5*val/360;            //แปลงหน่วยองศาเป็นรอบมอเตอร์
        val = round(val);               //ปัดเศษทศนิยมเป็นจำนวนเต็ม

        for (int j = 0; j < val; j++) counterclockwise();   //ลูปตามเข็มนาฬิกาตามจำนวนครั้งที่คำนวนไว้
        delay(3000);                                        //ดีเลย์ 3 วินาที
        for (int j = 0; j < val; j++) clockwise();          //หมุนเข็มกลับไปยังจุดเริ่มต้น
      }
    }
    Tex = "";
  }
}

void counterclockwise (){               //ฟังก์ชันเพื่อลูปตามเข็มนาฬิกา
  // 1
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay (motorSpeed);
  // 3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
}
void clockwise(){               //ฟังก์ชันเพื่อลูปทวนเข็มนาฬิกา
 // 1
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay (motorSpeed);
  // 3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
}
