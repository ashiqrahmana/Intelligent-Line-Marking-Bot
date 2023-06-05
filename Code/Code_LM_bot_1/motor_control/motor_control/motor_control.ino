
#include<RMCS2303drive.h>
#include<stdint.h>
//#include<string>
#include<Servo.h>
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
RMCS2303 motor;
Servo servo[4];

byte slaveID[] = {1,2,3,4}; 
long requiredSpeed=0;
int requiredAngle=90;
//----------------------------------------------------------------
//Setting up Software Serial communication
//----------------------------------------------------------------
      // Serial2 on pins 17 (RX) and 16 (TX),



void setup() {
  
  //Initiating Serial Communication with Motor Driver RMCS2303
  motor.Serial_selection(0);        //Using hardware Serial2 17(RX) and 16(TX)
  motor.Serial0(115200);
  motor.begin(&Serial2, 9600);
  servo[0].attach(2);
  servo[1].attach(3);
  servo[2].attach(5);
  servo[3].attach(6);
  servo[0].write(requiredAngle);
  servo[1].write(requiredAngle);
  servo[2].write(requiredAngle);
  servo[3].write(requiredAngle);
  servo[0].read();
  servo[1].read();
  servo[2].read();
  servo[3].read();  

  /*for (int i = 0; i++; i<4){
  //motor.WRITE_PARAMETER(slaveID, 0x0101, PGAIN, IGAIN, DGAIN, LPR, ACCELERATION, 1000 ); //Initialized motor in Speed Control mode enabled
    motor.EncoderPosition_LPR(slaveID[0], LPR);
    motor.Acceleration(slaveID[0], ACCELERATION);
    motor.ProportionalGain(slaveID[0], PGAIN);
    motor.IntegralGain(slaveID[0], IGAIN);
    motor.FeedforwardGain(slaveID[0], DGAIN);
    motor.Speed(slaveID[0], 2000);
    motor.Enable_Digital_Mode(slaveID[0], 1);
  }*/

  //motor.WRITE_PARAMETER(slaveID, 0x0101, PGAIN, IGAIN, DGAIN, LPR, ACCELERATION, 1000 ); //Initialized motor in Speed Control mode enabled
    motor.EncoderPosition_LPR(slaveID[0], LPR);
    motor.Acceleration(slaveID[0], ACCELERATION);
    motor.ProportionalGain(slaveID[0], PGAIN);
    motor.IntegralGain(slaveID[0], IGAIN);
    motor.FeedforwardGain(slaveID[0], DGAIN);
    motor.Speed(slaveID[0], 2000);
    motor.Enable_Digital_Mode(slaveID[0], 1);

  
  //motor.WRITE_PARAMETER(slaveID, 0x0101, PGAIN, IGAIN, DGAIN, LPR, ACCELERATION, 1000 ); //Initialized motor in Speed Control mode enabled
    motor.EncoderPosition_LPR(slaveID[1], LPR);
    motor.Acceleration(slaveID[1], ACCELERATION);
    motor.ProportionalGain(slaveID[1], PGAIN);
    motor.IntegralGain(slaveID[1], IGAIN);
    motor.FeedforwardGain(slaveID[1], DGAIN);
    motor.Speed(slaveID[1], 2000);
    motor.Enable_Digital_Mode(slaveID[1], 1);
 
  //motor.WRITE_PARAMETER(slaveID, 0x0101, PGAIN, IGAIN, DGAIN, LPR, ACCELERATION, 1000 ); //Initialized motor in Speed Control mode enabled
    motor.EncoderPosition_LPR(slaveID[2], LPR);
    motor.Acceleration(slaveID[2], ACCELERATION);
    motor.ProportionalGain(slaveID[2], PGAIN);
    motor.IntegralGain(slaveID[2], IGAIN);
    motor.FeedforwardGain(slaveID[2], DGAIN);
    motor.Speed(slaveID[2], 2000);
    motor.Enable_Digital_Mode(slaveID[2], 1);
    
  //motor.WRITE_PARAMETER(slaveID, 0x0101, PGAIN, IGAIN, DGAIN, LPR, ACCELERATION, 1000 ); //Initialized motor in Speed Control mode enabled
    motor.EncoderPosition_LPR(slaveID[3], LPR);
    motor.Acceleration(slaveID[3], ACCELERATION);
    motor.ProportionalGain(slaveID[3], PGAIN);
    motor.IntegralGain(slaveID[3], IGAIN);
    motor.FeedforwardGain(slaveID[3], DGAIN);
    motor.Speed(slaveID[3], 2000);
    motor.Enable_Digital_Mode(slaveID[3], 1);
}
void loop() {
  if(Serial.available()>0){
    
    String rawString = Serial.readStringUntil('n');
      servo[0].read();
      servo[1].read();
      servo[2].read();
      servo[3].read();     
   /*     switch(rawString[0]){
      case 0x01:
                rawString.remove(0);
                requiredAngle = rawString.toInt();
                myservo.write(requiredAngle);    
                break;
      case 0x11:
                rawString.remove(0);
                requiredSpeed = rawString.toInt(); 
                motor.Speed(slaveID, requiredSpeed);
                break; 
    }*/
  String c = String(rawString[0]); 
  if(rawString[0] == '0' || rawString[0] == '1' || rawString[0] == '2' || rawString[0] == '3'){
                rawString.remove(0,1);
                requiredAngle = rawString.toInt();
                servo[c.toInt()].write(requiredAngle); 
  }
  else if(rawString[0] == '4' || rawString[0] == '5' || rawString[0] == '6' || rawString[0] == '7'){
                rawString.remove(0,1);
                requiredSpeed = rawString.toInt(); 
                motor.Speed(slaveID[c.toInt()-4], requiredSpeed);
  }
  
}
}
/*
#include<RMCS2303drive.h>
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
RMCS2303 motor;

byte slaveID[] = {0x07}; 
long requiredSpeed=0;
int requiredAngle=90;
//----------------------------------------------------------------
//Setting up Software Serial communication
//----------------------------------------------------------------
      // Serial2 on pins 17 (RX) and 16 (TX),



void setup() {
  
  //Initiating Serial Communication with Motor Driver RMCS2303
  motor.Serial_selection(0);        //Using hardware Serial2 17(RX) and 16(TX)
  motor.Serial0(115200);
  motor.begin(&Serial1, 9600);

    
  //motor.WRITE_PARAMETER(slaveID, 0x0101, PGAIN, IGAIN, DGAIN, LPR, ACCELERATION, 1000 ); //Initialized motor in Speed Control mode enabled
    motor.EncoderPosition_LPR(slaveID[0], LPR);
    motor.Acceleration(slaveID[0], ACCELERATION);
    motor.ProportionalGain(slaveID[0], PGAIN);
    motor.IntegralGain(slaveID[0], IGAIN);
    motor.FeedforwardGain(slaveID[0], DGAIN);
    motor.Speed(slaveID[0], 2000);
    motor.Enable_Digital_Mode(slaveID[0], 1);
}
void loop() {
    motor.Speed(slaveID[0], requiredSpeed);
}*/
