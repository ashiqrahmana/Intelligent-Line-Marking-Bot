/*
#include<RMCS2303drive.h>
#include<stdint.h>

//----------------------------------------------------------------
//#defines
//----------------------------------------------------------------
#define SLAVE1        0
#define SLAVE2        1

#define IGAIN         32
#define DGAIN         16
#define LPR           11
#define ACCELERATION  20000

//----------------------------------------------------------------
//Structure definition
//----------------------------------------------------------------
typedef struct{
#define PGAIN         100
  long int currentPosition, currentSpeed;
}motorFeedback;

//----------------------------------------------------------------
//Function declaration
//----------------------------------------------------------------
void waitTillPositionReached(long int);

//----------------------------------------------------------------
//Global variables
//----------------------------------------------------------------
RMCS2303 motor;
motorFeedback slave[2];
int slaveID = 7;

//----------------------------------------------------------------
//Setting up Software Serial communication
//----------------------------------------------------------------
SoftwareSerial myserial(2, 3);      //RX - 2, TX - 3



void setup() {
  //Initiating Serial Communication with Motor Driver RMCS2303
  motor.Serial_selection(1);
  motor.begin(&myserial, 9600);

  Serial.begin(115200);
  motor.WRITE_PARAMETER(slaveID, 0x0101, PGAIN, IGAIN, DGAIN, LPR, ACCELERATION, 3000); //Initialized motor in Postion Control mode disabled
  //motor.SET_HOME(slaveID);
  

  //motor.Enable_Digital_Mode(slaveID, 0);
  
 }

void loop() {
    
    long int speedFeedback = motor.Speed_Feedback(slaveID);
    String toBeSent = String(speedFeedback)+'\n';
    Serial.print(toBeSent);
    //motor.Speed(7, 10);
    /*
    if(Serial.available()>0){
      String inputSpeed = Serial.readStringUntil('\n');
      motor.Speed(slaveID, inputSpeed.toInt());  
      //delay(2000);
    }
}
//----------------------------------------------------------------
//Function definition
//----------------------------------------------------------------
void waitTillPositionReached(long int pos){
          uint8_t positionReached;
          long int positionDifference;
          while(1){
          for(slaveID = 1; slaveID <= 2; slaveID++){
            
            slave[slaveID-1].currentPosition = motor.Position_Feedback(slaveID);
            positionDifference =  motor.Position_Feedback(slaveID) - slave[slaveID-1].currentPosition;

            positionDifference = (positionDifference < 0)? -positionDifference: positionDifference;
            positionReached = (positionDifference < 20)? 1 : 0;
            
            slave[slaveID-1].currentSpeed = motor.Speed_Feedback(slaveID);
          }
          
          if(positionReached){
            break;
          }
        }
}*/
/*
Connections of Drive and Arduino
Serial Port 0 is not used to connect to drive because its connected to USB-Serial and used to show information on console.

For Arduino Uno Software serial needs to be used as there is only one hardware serial port and its connected to USB-Serial. 
   Drive to Arduino UNO/Nano connections
   GND         -      GND
   RXD         -      D3
   TXD         -      D2

For arduino mega and other arduinos with multiple hardware serial port, any port other than 0 can be selected to connect the drive.

   Drive to Arduino Mega2560 connections
   GND         -      GND
   RXD         -      Tx1/Tx2/Tx3
   TXD         -      Rx1/Rx2/Rx3
   
*  This mode can be used when multiple motors are to be used to run at exactly the same RPM and same torque even though the voltage supply might be different.
* Also in this mode the direction of the motor can be controlled digitally via modbus ASCII commands to run the dc servo motor in both directions

* For more information see : https://robokits.co.in/motor-drives-drivers/encoder-dc-servo/rhino-dc-servo-driver-50w-compatible-with-modbus-uart-ascii-for-encoder-dc-servo-motor


*/
/*
#include<RMCS2303drive.h>

RMCS2303 rmcs;                    //object for class RMCS2303

SoftwareSerial myserial(0,1);     //Software Serial port For Arduino Uno. Comment out if using Mega.

//parameter Settings "Refer datasheet for details"
byte slave_id=7 ;
int INP_CONTROL_MODE=257;           
int PP_gain= 100;
int PI_gain=32;
int VF_gain=16;
int LPR=11;
int acceleration=20000;
int speed_=9000;


long int Current_position;
long int Current_Speed;

void setup()
{
   Serial.begin(9600);
   rmcs.Serial_selection(1);       //Serial port selection:0-Hardware serial,1-Software serial
   rmcs.Serial0(9600);             //Set baudrate for usb serial to monitor data on serial monitor
   Serial.println("RMCS-2303 Speed control mode demo\r\n\r\n");
   Serial.println("-");
   //rmcs.begin(&Serial1,9600);    //Uncomment if using hardware serial port for mega2560:Serial1,Serial2,Serial3 and set baudrate. Comment this line if Software serial port is in use
   rmcs.begin(&myserial,9600);     //Uncomment if using software serial port. Comment this line if using hardware serial.
   Serial.println("-");
   rmcs.READ_PARAMETER(slave_id);
   Serial.println("-");
   rmcs.WRITE_PARAMETER(slave_id,INP_CONTROL_MODE,PP_gain,PI_gain,VF_gain,LPR,acceleration,speed_);    //Uncomment to write parameters to drive. Comment to ignore.
   //Serial.println("-");
}

void loop(void)
{
   Serial.println("looping bruh");
   Serial.println("Sending speed command - 8000 RPM");
   rmcs.Speed(slave_id,1000);                   //Set speed within range of 0-65535 or 0-(maximum speed of base motor)
   rmcs.Enable_Digital_Mode(slave_id,0);        //To enable motor in digital speed control mode. 0-fwd,1-reverse direction. 
   
   delay(3000);
   Current_Speed=rmcs.Speed_Feedback(slave_id); 
   Serial.print("Current Speed feedback : ");
   Serial.println(Current_Speed);

   delay(5000);
   Serial.println("Break Motor");
   rmcs.Brake_Motor(slave_id,0);                 //Brake motor. 0-fwd,1-reverse direction. 

   delay(2000);
   Serial.println("Changing direction");
   rmcs.Enable_Digital_Mode(slave_id,1);           //To enable motor in digital speed control mode. 0-fwd,1-reverse direction. 
}*/
#include<RMCS2303drive.h>
#include<stdint.h>

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
int slaveID=0x07;

//----------------------------------------------------------------
//Setting up Software Serial communication
//----------------------------------------------------------------
      // Serial2 on pins 17 (RX) and 16 (TX),



void setup() {
  //Initiating Serial Communication with Motor Driver RMCS2303
  motor.Serial_selection(0);        //Using hardware Serial2 17(RX) and 16(TX)
  motor.Serial0(9600);
  motor.begin(&Serial2, 9600);

  
  motor.WRITE_PARAMETER(slaveID, 0x0200, PGAIN, IGAIN, DGAIN, LPR, ACCELERATION, 0); //Initialized motor in Speed Control mode disabled
  motor.Enable_Digital_Mode(slaveID,1);   //Enables digital speed control mode in CW direction
  motor.Speed(slaveID, 7770);

  delay(2000);

  motor.Speed(slaveID, -7770);
 }

void loop() {
  
  long requiredSpeed;
  if(Serial.available()>0){
    uint8_t serByte;
    for(uint8_t i=0; i<4; i++){   //If data available in serial buffer, read 4 bytes
      serByte = Serial.read();
      requiredSpeed |= ((long)serByte)<<(i*8);
    }
    motor.Speed(slaveID, requiredSpeed);

    delay(2000);
    int actualSpeed = motor.Speed_Feedback(slaveID);

    uint8_t buff[4];
    buff[0]= actualSpeed & 0xFF;
    buff[1]= (actualSpeed >> 8) & 0xFF;
    buff[2]= (actualSpeed >> 16) & 0xFF;
    buff[3]= (actualSpeed >> 24) & 0xFF;
    Serial.write(buff, sizeof(buff));
  }

  
}
//----------------------------------------------------------------
//Function definition
//----------------------------------------------------------------

//----------------------------------------------------------------
//Python code on receiving end
//----------------------------------------------------------------
/*
import struct
import serial

with serial.Serial('\dev\ttyACM0',115200) as file:
  file.flushInput();
  file.flushOutput();
  while(True):
    userInput = int(input("Enter speed: "))
    byteInput = struct.pack('!l',userInput)
    file.write(byteInput)

    receivedData = file.read(4)
    print(struct.unpack('!l',receivedData))
*/
