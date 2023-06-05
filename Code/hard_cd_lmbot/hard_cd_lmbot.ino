#include<Servo.h>

Servo servo[4];

int IN1[] = {35,37,39,41};
int IN2[] = {34,36,38,40};
int EN[] = {50,51,52,53};

void setup() {
  Serial.begin(115200);
    
  // put your setup code here, to run once:
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    for (int i = 0;i < 4; i++){
      pinMode(IN1[i],OUTPUT);
      pinMode(IN2[i],OUTPUT);
      pinMode(EN[i],INPUT);      
    }
    servo[0].attach(2);
    servo[1].attach(3);
    servo[2].attach(4);
    servo[3].attach(5);
    servo[0].write(90);
    servo[1].write(90);
    servo[2].write(90);
    servo[3].write(90);
    for (int i = 0;i < 4; i++){
      digitalWrite(IN1[i],LOW);
      digitalWrite(IN2[i],LOW);      
    }

  digitalWrite(IN1[0],HIGH);
  digitalWrite(IN2[0],LOW);
  digitalWrite(EN[0],100);

  digitalWrite(IN1[1],HIGH);
  digitalWrite(IN2[1],LOW);
  digitalWrite(EN[1],100);
  
  digitalWrite(IN1[2],HIGH);
  digitalWrite(IN2[2],LOW);
  digitalWrite(EN[2],100);
  
  digitalWrite(IN1[3],HIGH);
  digitalWrite(IN2[3],LOW);
  digitalWrite(EN[3],100);    delay(10000);

  digitalWrite(IN1[0],LOW);
  digitalWrite(IN2[0],LOW);
  digitalWrite(EN[0],100);

  digitalWrite(IN1[1],LOW);
  digitalWrite(IN2[1],LOW);
  digitalWrite(EN[1],100);
  
  digitalWrite(IN1[2],LOW);
  digitalWrite(IN2[2],LOW);
  digitalWrite(EN[2],100);
  
  digitalWrite(IN1[3],LOW);
  digitalWrite(IN2[3],LOW);
  digitalWrite(EN[3],100);
    delay(2000);
  digitalWrite(IN1[0],HIGH);
  digitalWrite(IN2[0],LOW);
  digitalWrite(EN[0],100);

  digitalWrite(IN1[1],LOW);
  digitalWrite(IN2[1],HIGH);
  digitalWrite(EN[1],100);
  
  digitalWrite(IN1[2],HIGH);
  digitalWrite(IN2[2],LOW);
  digitalWrite(EN[2],100);
  
  digitalWrite(IN1[3],LOW);
  digitalWrite(IN2[3],HIGH);
  digitalWrite(EN[3],100);
    delay(5000);
  digitalWrite(IN1[0],HIGH);
  digitalWrite(IN2[0],LOW);
  digitalWrite(EN[0],100);

  digitalWrite(IN1[1],HIGH);
  digitalWrite(IN2[1],LOW);
  digitalWrite(EN[1],100);
  
  digitalWrite(IN1[2],HIGH);
  digitalWrite(IN2[2],LOW);
  digitalWrite(EN[2],100);
  
  digitalWrite(IN1[3],HIGH);
  digitalWrite(IN2[3],LOW);
  digitalWrite(EN[3],100);
    delay(5000);
    for (int i = 0;i < 4; i++){
      digitalWrite(IN1[i],LOW);
      digitalWrite(IN2[i],LOW);      
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
