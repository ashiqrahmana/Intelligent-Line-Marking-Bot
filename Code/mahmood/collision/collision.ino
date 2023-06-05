//#include <Wire.h>
//#include "Adafruit_VL53L0X.h"
//#include <Servo.h>
//
//Adafruit_VL53L0X vl = Adafruit_VL53L0X();
//Servo myservo;
//
//float pos = 0;
//const float Pi = 3.14159;
//
//void setup(){
//  myservo.attach(9);
//  Serial.begin(115200);
// /* while(!Serial){
//    delay(1);
//  }
//  
//  if(!vl.begin()){
//    while(1);
//  }*/  
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//for(pos = 0;pos<=180;pos+=0.5){
//  myservo.write(pos);
//  //uint8_t range = vl.readRange();
//  //VL53L0X_RangingMeasurementData_t measure; 
//  //Serial.println(String(measure.RangeMilliMeter)+"p"+String((pos*Pi)/180)+"p"+String(pos));
//  delay(10);
//}
//
//  myservo.write(0);
//  delay(1000);
//}

#include "Adafruit_VL53L0X.h"
#include <Servo.h>

Servo servo;

float range;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  servo.attach(9);
  servo.write(0);
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

float lidar(){
  VL53L0X_RangingMeasurementData_t measure;
    
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    range = float(measure.RangeMilliMeter);
  } 
  else {
    Serial.println(" out of range ");
  }
  return range;
}

void loop() {
    for(float pos = 0;pos<=180;pos+=0.5){
        servo.write(pos);
        range = lidar();
        Serial.print(range);
        Serial.print(",");
        Serial.println(pos);
        delay(10);
    }
    for(float pos = 180;pos>=0;pos-=0.5){
        servo.write(pos);
        range = lidar();
        Serial.print(range);
        Serial.print(",");
        Serial.println(pos);
        delay(10);
    }
}
