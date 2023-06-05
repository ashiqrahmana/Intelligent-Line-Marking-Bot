#include "MPU9250.h"

#include <TinyGPS++.h>
#include <Servo.h>
#include "Adafruit_VL53L0X.h"
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

long requiredSpeed=0;
int requiredAngle=90;
//----------------------------------------------------------------
//Setting up Software Serial communication
//----------------------------------------------------------------
// Serial2 on pins 17 (RX) and 16 (TX),
// The serial connection to the GPS device

void init_qmc();
void init_motors();
void drive_motor();

float getPhi();
int lidar();

const int M1A[4] = {2,4,6,8};
const int M1B[4] = {3,5,7,9};

float prev_t = millis();
float prev_w = 0;

Servo scanner;
Servo slider;
int pos = 0;
float range;
bool returningToZero;
int s[19];
int l;
int k = 0;
int dirn ;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int countfl = 0;
int countf = 0;
int countfr = 0;

void setup() {
    Serial.begin(115200);
    init_servo();
    // wait until serial port opens for native USB devices
    while (! Serial) {
     delay(1);
    }
    Wire.begin();  // probably try commenting this man cuz the wire gets intialised while intialising lidar
    Serial1.begin(GPSBaud);
    Serial.println("Initiating initialisation");
    //To change the default settings of the MPU
    //uploadCalibrationData();    
    init_rmcs();
    
    Serial.println(" QMC START");
    init_lidar();
    mpu.setup(0x68);
    init_qmc();
    Serial.println(" QMC FINISH");
    for (int i = 0;i < 4; i++){
      analogWrite(M1A[i],0);
      analogWrite(M1B[i],0);      
    }
    Serial.println(" QMC MOTOR DRIVER");
    //randomSeed(analogRead(0));
    //Serial.println(" RANDOM ");
}

void loop() {
    if (mpu.update()){
      if (gps.location.isUpdated() && gps.location.isValid()){
          gps.encode(Serial1.read());
          lat_ = gps.location.lat();
          long_ = gps.location.lng();
          speed_ = gps.speed.mps();
        }
        else{
          lat_ += 0.0001; 
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
      for (int a=0;a<19;a++)
          int dirn = lidar();
        
      Serial.print(lat_, 6);
      Serial.print("/");Serial.print(long_, 6);
      Serial.print("/");Serial.print(phi);
      Serial.print("/");Serial.print(speed_*cos(phi));
      Serial.print("/");Serial.print(speed_*sin(phi)); 
      Serial.print("/");Serial.println(w);     
  }
  int i = 0;
  while(i<100){
    serialInput();
    i++;
  }
}
