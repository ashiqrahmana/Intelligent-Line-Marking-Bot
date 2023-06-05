#include "MPU9250.h"

#include <TinyGPS++.h>
#include <Servo.h>
//-----------------------#defines--------------------------//
#define MPU_ADDR 0x68

//-----------------------Function headers--------------------------//
void uploadCalibrationData();

//-----------------------All object declarations--------------------------//
MPU9250 mpu;
TinyGPSPlus gps;

//-----------------------GLOBAL VARIABLES--------------------------//
static const uint32_t GPSBaud = 9600;

const float Ares = 16.0f/32768.0f;       //Since using +-8G
const float Gres = 2000.0f/32768.0f;            //Since sing 1000 DPS

float gyroDataInDPS[3];
int16_t rawGyroData[3];

float yaw = 0.0, pitch = 0.0, roll = 0.0;
float lat_ =13.0000, long_ = 80.0000, speed_ = 0;

//----------------------------------------------------------------
//Global variables
//----------------------------------------------------------------

Servo servo[4];

byte slaveID[] = {0x01,0x02,0x03,0x04}; 
long requiredSpeed=0;
int requiredAngle=90;
//----------------------------------------------------------------
//Setting up Software Serial communication
//----------------------------------------------------------------
// Serial2 on pins 17 (RX) and 16 (TX),
// The serial connection to the GPS device
//SoftwareSerial S(RXPin, TXPin);
void init_qmc();
void init_motors();
void drive_motor();
float getPhi();
//int lidar();
int IN1[] = {34,36,38,40};
int IN2[] = {35,37,39,41};
int EN[] = {50,51,52,53};

float prev_t = millis();
float prev_w = 0;
        
void setup() {
    Serial.begin(115200);
    Wire.begin();
    Serial1.begin(GPSBaud);
    Serial.println("Initiating initialisation");
    //To change the default settings of the MPU
    //uploadCalibrationData();
    
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    
    //init_rmcs();
    
    servo[0].attach(2);
    servo[1].attach(3);
    servo[2].attach(4);
    servo[3].attach(5);
    servo[0].write(90);
    servo[1].write(90);
    servo[2].write(90);
    servo[3].write(90);
    
    Serial.println(" QMC START");
    mpu.setup(0x68);
    init_qmc();
    Serial.println(" QMC FINISH");
    for (int i = 0;i < 4; i++){
      digitalWrite(IN1[i],LOW);
      digitalWrite(IN2[i],LOW);      
    }
    Serial.println(" QMC MOTOR DRIVER");
    randomSeed(analogRead(0));
    Serial.println(" RANDOM ");
}

void loop() {
    //Serial.println(Serial1.available());
    //Serial.println(servo[0].read());
    //Serial.println(servo[1].read());
    //Serial.println(servo[2].read());
    //Serial.println(servo[3].read());
    if (mpu.update()){
      if (gps.location.isUpdated()){
        gps.encode(Serial1.read());
        lat_ = gps.location.lat();
        long_ = gps.location.lng();
        speed_ = gps.speed.mps();
        }
        else{
          lat_ += 0.0001; //random(13.0109,13.0130);
          long_ += 0.0001;
          speed_ += 0.0001;
        }
      //Serial.print("/");Serial.print(heading);Serial.print("g");        
      //Getting RAW GYRO DATA from the sensor
      
//        for(uint8_t i=0; i<3; i++){
//          rawGyroData[i] = mpu.getGyro(i);
//        }
//        
//        //Computing GYRO DATA IN DEGREE PER SECOND
//        for(uint8_t i=0; i<3; i++){
//          gyroDataInDPS[i] = rawGyroData[i]*Gres;  
//        }     
      
      float curr_w = mpu.getYaw();
      float del_w = curr_w - prev_w;
      float del_t = millis() - prev_t;
      float w = del_w / del_t;
      prev_t = millis();
      prev_w = curr_w;
      
      float phi = getPhi();
      //int dirn = lidar();
        
      Serial.print(lat_, 6);
      Serial.print("/");Serial.print(long_, 6);
      Serial.print("/");Serial.print(phi);
      Serial.print("/");Serial.print(speed_*cos(phi));
      Serial.print("/");Serial.print(speed_*sin(phi)); 
      Serial.print("/");Serial.println(w);
      //Serial.print("/");Serial.println(dirn);
      
      /*Serial.print(gyroDataInDPS[0]);Serial.print("/");
      Serial.print(gyroDataInDPS[1]);Serial.print("/");*/     
  }
  if (Serial.available() > 0){  
    String rawString = Serial.readStringUntil('n');
    String c = String(rawString[0]); 
    if(rawString[0] == '0' || rawString[0] == '1' || rawString[0] == '2' || rawString[0] == '3'){
      rawString.remove(0,1);
      requiredAngle = rawString.toInt();
      servo[c.toInt()].write(requiredAngle );
    }
    else if (rawString[0] == '4' || rawString[0] == '5' || rawString[0] == '6' || rawString[0] == '7'){
      rawString.remove(0,1);
      requiredSpeed = map(rawString.toInt(),0,9000,0,255);
      // Turn on motors
      //digitalWrite(IN1[c.toInt()-4], LOW);
      //digitalWrite(IN2[c.toInt()-4], HIGH);
      //analogWrite(EN[c.toInt()-4], requiredSpeed);
      //rmcs_control(requiredSpeed,c.toInt()-4);
      analogWrite(M1A[i],requiredSpeed);//C
      analogWrite(M1B[i],0);
    }
    Serial.flush();    
  }
  delay(1000);
}
