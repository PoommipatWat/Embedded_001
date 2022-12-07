int motorPin1 = 23;// Blue   - 28BYJ48 pin 1
int motorPin2 = 22;// Pink   - 28BYJ48 pin 2
int motorPin3 = 21;// Yellow - 28BYJ48 pin 3
int motorPin4 = 19;// Orange - 28BYJ48 pin 4
int motorSpeed = 4;     //variable to set stepper speed

double begin_degree = 13.8461538461538;
char inp;
double val;
int left;

void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}



//first
void loop() {
  if (Serial.available() > 0) {
    val = 0;
    inp = Serial.read();

    Serial.println(inp);

    val = inp;
    val = val-65;
    Serial.println(val);
    val *= begin_degree;
    Serial.println(val);
    val = 512.5*val/360;
    val = round(val);
    Serial.println(val);


    for (int j = 0; j < val; j++) counterclockwise();
    delay(3000);
    for (int j = 0; j < val; j++) clockwise();    

  }
}

// second
// void loop (){
//   if (Serial.available() > 0) {
//     val = 0;
//     inp = Serial.read();

//     Serial.println(inp);

//     val = inp;
//     val = val-65;
//     Serial.println(val);
//     val *= begin_degree;
//     Serial.println(val);
//     val = 512.5*val/360;
//     val = round(val);
//     Serial.println(val);

//     for (int j = 0; j < val; j++) counterclockwise();
//     delay(3000);

//     left = 512-val;
//     Serial.println(left);
//     for (int j = 0; j < left; j++) counterclockwise();


//   }
// }

void stop(){
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW); 
}

void counterclockwise (){
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
void clockwise(){
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