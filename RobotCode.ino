#include <Servo.h>
Servo sally;
const int ENA = 6;
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 9;
const int IN4 = 10;
const int ENB = 11;
int trig = 2;
int echo = 3;
long duration;
int distance;
int Rdist;
int Ldist;
int Hdist;

void Forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void Back() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(500);
}
void Left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(500);
}
void Read() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034/2;
}
void Lright() {
 sally.write(0);
 delay(2000);
 Read();
 Rdist = distance;
 sally.write(90);
 delay(2000);
}
void Lleft() {
 sally.write(180);
 delay(2000);
 Read();
 Ldist = distance;
 sally.write(90);
 delay(2000);
}
void Lhome() {
 Read();
 Hdist = distance;
}



void setup() {

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, 115);
  analogWrite(ENB, 80);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  
  sally.attach(4);
  sally.write(90);
  delay(2000);
}

void loop() {
  Serial.begin(9600);
  Serial.println(distance);
  
  Lhome();
  if (Hdist > 50){
    Forward();
  }
  else {
    Stop();
    Lright();
    Lleft();
    if (Rdist > Ldist){
      Right();
    }
    else if (Rdist < Ldist){
      Left();
    }
  }
}
