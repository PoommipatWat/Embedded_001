// #define motorPin1 23// Blue   - 28BYJ48 pin 1

// void setup() {

//   pinMode(motorPin1, OUTPUT);       //ประกาศตัวแปร motorPin1 เป็น output

//   Serial.begin(9600);               //ประกาศ Serial ที่ 9600

// }

// void loop() {
//   digitalWrite(motorPin1, HIGH);
//   delay(5000);
//   digitalWrite(motorPin1, LOW);
//   delay(5000);

// }

//---------------------------------------------------------------------------------------------------------------------------------

// #include <WiFi.h>
// #include <MQTT.h>

// #define Button 23

// const char ssid[] = "imb24";
// const char pass[] = "12345678";

// const char mqtt_broker[]="test.mosquitto.org";
// const char mqtt_topic[]="group7/command";
// int MQTT_PORT=1883;

// int counter=0;

// WiFiClient net;
// MQTTClient client;

// unsigned long lastMillis = 0;

// void connect() {
//   Serial.print("checking wifi...");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print(".");
//     delay(1000);
//   }

//   Serial.print("\nconnecting...");
//   while (!client.connect("arduino_group_7")) {  // connection ID should be unique
//     Serial.print(".");
//     delay(1000);
//   }

//   Serial.println("\nconnected!");

//   client.subscribe(mqtt_topic);
//   // client.unsubscribe("/hello");
// }

// void messageReceived(String &topic, String &payload) {
//   Serial.println("incoming: " + topic + " - " + payload);

//   // Note: Do not use the client in the callback to publish, subscribe or
//   // unsubscribe as it may cause deadlocks when other things arrive while
//   // sending and receiving acknowledgments. Instead, change a global variable,
//   // or push to a queue and handle it in the loop after calling `client.loop()`.
// }

// void setup() {
//   Serial.begin(9600);
//   WiFi.begin(ssid, pass);

//   // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
//   // by Arduino. You need to set the IP address directly.
//   client.begin(mqtt_broker, MQTT_PORT, net);
//   client.onMessage(messageReceived);

//   pinMode(Button, INPUT_PULLUP);

//   connect();
// }

// void loop() {
//   client.loop();
//   delay(10);  // <- fixes some issues with WiFi stability

//   if (!client.connected()) {
//     connect();
//   }

//   // publish a message roughly every second.
//   // not that we don't use delay() because we need to keep calling the client.loop()
//   // to keep the connection alive
//   if (millis() - lastMillis > 2000) {
//     lastMillis = millis();
//     if(digitalRead(Button) == LOW){
//       client.publish(mqtt_topic, "Button Pressed");
//     }
//     else{
//       client.publish(mqtt_topic, "Button Released");
//     }
//     // client.publish(mqtt_topic, "Counter = " + String(counter++));
//   }
// }


// #include <WiFi.h>
// #include <MQTT.h>

// #define Button 23

// const char ssid[] = "imb24";
// const char pass[] = "12345678";

// const char mqtt_broker[]="test.mosquitto.org";
// const char mqtt_topic[]="group7/command";
// int MQTT_PORT=1883;

// int counter=0;

// String Tex;

// WiFiClient net;
// MQTTClient client;

// unsigned long lastMillis = 0;

// void connect() {
//   Serial.print("checking wifi...");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print(".");
//     delay(1000);
//   }

//   Serial.print("\nconnecting...");
//   while (!client.connect("arduino_group_7")) {  // connection ID should be unique
//     Serial.print(".");
//     delay(1000);
//   }

//   Serial.println("\nconnected!");

//   client.subscribe(mqtt_topic);
//   // client.unsubscribe("/hello");
// }

// void messageReceived(String &topic, String &payload) {
//   Serial.println("incoming: " + topic + " - " + payload);
//   Tex = payload;

//   // Note: Do not use the client in the callback to publish, subscribe or
//   // unsubscribe as it may cause deadlocks when other things arrive while
//   // sending and receiving acknowledgments. Instead, change a global variable,
//   // or push to a queue and handle it in the loop after calling `client.loop()`.
// }

// void setup() {
//   Serial.begin(9600);
//   WiFi.begin(ssid, pass);

//   // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
//   // by Arduino. You need to set the IP address directly.
//   client.begin(mqtt_broker, MQTT_PORT, net);
//   client.onMessage(messageReceived);

//   pinMode(Button, OUTPUT);

//   connect();
// }

// void loop() {
//   client.loop();
//   delay(10);  // <- fixes some issues with WiFi stability

//   if (!client.connected()) {
//     connect();
//   }

//   // publish a message roughly every second.
//   // not that we don't use delay() because we need to keep calling the client.loop()
//   // to keep the connection alive
//   if (millis() - lastMillis > 2000) {
//     lastMillis = millis();
//     if(Tex == "ON") digitalWrite(Button, HIGH);
//     else if(Tex == "OFF") digitalWrite(Button, LOW);
//     else digitalWrite(Button, LOW);
//     // client.publish(mqtt_topic, "Counter = " + String(counter++));
//   }
// }

#include <WiFi.h>
#include <MQTT.h>

#define Button 23

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

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  pinMode(Button, OUTPUT);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  // not that we don't use delay() because we need to keep calling the client.loop()
  // to keep the connection alive
  if (millis() - lastMillis > 2000) {
    lastMillis = millis();
    if(Tex == "ON") digitalWrite(Button, HIGH);
    else if(Tex == "OFF") digitalWrite(Button, LOW);
    else digitalWrite(Button, LOW);
    // client.publish(mqtt_topic, "Counter = " + String(counter++));
  }
}