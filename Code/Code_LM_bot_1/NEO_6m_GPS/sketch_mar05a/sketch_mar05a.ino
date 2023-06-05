#include <Servo.h>
#include <string.h>

//definition
Servo dem;
String ser = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dem.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0){
   ser = Serial.readStringUntil('\n');
   dem.write(ser.toInt()); 
  }
}
