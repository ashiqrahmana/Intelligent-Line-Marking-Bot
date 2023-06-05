#include<RMCS2303drive.h>

//define s
#define PGAIN         100
#define IGAIN         32
#define VFGAIN        16
#define LPR           11
#define ACCELERATION  20000
#define SPEED         5000

//struct rmcsSetting{
//  byte slaveID;
//  int input_control_mode, P_gain, I_gain, VF_gain, lpr, m_acceleration, m_speed;
//};
//typedef struct rmcsSetting rmcsSetting;


//!!!!  Using SLAVEID 1 !!!!!
//rmcsSetting motor1={1,257,PGAIN,IGAIN,VFGAIN,11,ACCELERATION, SPEED};
RMCS2303 rmcs;              //Object instantiation

void setup(){
  rmcs.Serial_selection(0);
  rmcs.Serial0(9600);
  Serial.println("RMCS2303 recognized!!!");

  rmcs.begin(&Serial1,9600);        //Connect RMCSServo to Hardware Serial 1
  
  //rmcs.WRITE_PARAMETER(motor1.slaveID, motor1.input_control_mode,motor1.P_gain,motor1.I_gain, motor1.VF_gain,motor1.lpr,motor1.m_acceleration, motor1.m_speed);
  rmcs.WRITE_PARAMETER(byte(7),257,100,32,16,11,20000,5000);
  rmcs.READ_PARAMETER(byte(7));
  
  rmcs.Speed(byte(7), SPEED);
  rmcs.Enable_Digital_Mode(byte(7),0);   //Clockwise rotation @5000 rpm
}

void loop(){
  
}
