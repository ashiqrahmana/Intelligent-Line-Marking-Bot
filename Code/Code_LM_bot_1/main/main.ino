#include "MPU9250.h"

#include <TinyGPS++.h>
#include<Servo.h>
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
float lat_ = 0.0, long_ = 0.0, speed_ = 0.0;

//----------------------------------------------------------------
//#defines
//----------------------------------------------------------------
#define SLAVE1        0
#define SLAVE2        1

#define PGAIN         100
#define IGAIN         32
#define DGAIN         16
#define LPR           11
#define ACCELERATION  20000

//----------------------------------------------------------------
//Structure definition
//----------------------------------------------------------------

//----------------------------------------------------------------
//Function declaration
//----------------------------------------------------------------


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
int IN1[] = {34,36,38,40};
int IN2[] = {35,37,39,41};
int EN[] = {50,51,52,53};
void setup() {
    Serial.begin(115200);
    Wire.begin();
    Serial1.begin(GPSBaud);
    
    //To change the default settings of the MPU
    //uploadCalibrationData();
    MPU9250Setting setting;
    setting.accel_fs_sel = ACCEL_FS_SEL::A16G;
    setting.gyro_fs_sel = GYRO_FS_SEL::G2000DPS;
    setting.mag_output_bits = MAG_OUTPUT_BITS::M16BITS;
    setting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_200HZ;
    setting.gyro_fchoice = 0x03;
    setting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_41HZ;
    setting.accel_fchoice = 0x01;
    setting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_45HZ;
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    for (int i = 0;i < 4; i++){
      pinMode(IN1[i],OUTPUT);
      pinMode(IN2[i],OUTPUT);
      pinMode(EN[i],OUTPUT);      
    }
    servo[0].attach(2);
    servo[1].attach(3);
    servo[2].attach(4);
    servo[3].attach(5);
    servo[0].write(90);
    servo[1].write(90);
    servo[2].write(90);
    servo[3].write(90);
    mpu.setup(0x68, setting);
    init_qmc();
    for (int i = 0;i < 4; i++){
      digitalWrite(IN1[i],LOW);
      digitalWrite(IN2[i],LOW);      
    }}

void loop() {
    //Serial.println(Serial1.available());
    while (Serial1.available() > 0)
    {
      
      //Serial.println(servo[0].read());
      //Serial.println(servo[1].read());
      //Serial.println(servo[2].read());
      //Serial.println(servo[3].read());
      gps.encode(Serial1.read());
      if (gps.location.isUpdated() && mpu.update()){
        lat_ = gps.location.lat();
        long_ = gps.location.lng();
        //float heading = gps.course.deg();
        speed_ = gps.speed.mps();
        //Serial.print("/");Serial.print(heading);Serial.print("g");        
        //Getting RAW GYRO DATA from the sensor
        for(uint8_t i=0; i<3; i++){
          rawGyroData[i] = mpu.getGyro(i);
        }
        
        //Computing GYRO DATA IN DEGREE PER SECOND
        for(uint8_t i=0; i<3; i++){
          gyroDataInDPS[i] = rawGyroData[i]*Gres;  
        }        
        float phi = getPhi();
        Serial.print(lat_, 6);
        Serial.print("/");Serial.print(long_, 6);
        Serial.print("/");Serial.print(phi);
        Serial.print("/");Serial.print(speed_*cos(phi));
        Serial.print("/");Serial.print(speed_*sin(phi)); 
        Serial.print("/");Serial.println(gyroDataInDPS[2]);
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
        digitalWrite(IN1[c.toInt()-4], LOW);
        digitalWrite(IN2[c.toInt()-4], HIGH);
        analogWrite(EN[c.toInt()-4], requiredSpeed);
      }
      Serial.flush();    
    }
}
}
