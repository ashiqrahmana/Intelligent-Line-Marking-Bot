// 512/360 = x/angle ==> angle = x*360/(512*4.8)
// angle/360 = dist / pi(D) 

#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp = 100, Ki = 50, Kd = 1;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

const int enA = 2;
const int enB = 3;

const int IN1 = 4; 
const int IN2 = 5;
const int ENA = 6;

float distance = 0;
float prev_distance = 0;
float velocity = 0;

float prev_ms = 0;

volatile bool A  = 0;
volatile bool B  = 0;

float GR = 0.50; //diameter = 0.135m

int COUNT = 0;

int dir = 1;

void enAUpdate(){
  A = !A;
  if (A == 1){
    if (A == B){
      distance += GR;
    }
    else if (A != B){
      distance -= GR;
    }
  }
}

void enBUpdate(){
  B = !B;
}

void init_encoder(){
  /* Setup the interrupt pin */
  // put your setup code here, to run once:
  pinMode(enA, INPUT);
  pinMode(enB, INPUT);
  attachInterrupt(digitalPinToInterrupt(enA), enAUpdate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(enB), enBUpdate, CHANGE);
}

void disp_values(){
  
  if (millis() > prev_ms+5){
      velocity = abs(distance - prev_distance)/ (millis() - prev_ms);
      prev_distance = distance;    
      Serial.print(velocity*dir);
      Serial.print(",");
//      Serial.print(distance);
//      Serial.print("\t");
      Serial.println(setpoint);
      //Serial.print("\t");
//      Serial.print(Input);
//      Serial.print("\t");
      //Serial.println(Output);
      prev_ms = millis();
  }
}

void init_PID(){
    setpoint = -1.5;
    Setpoint = abs(setpoint);
    myPID.SetMode(AUTOMATIC);
}

void setup()
{
  Serial.begin(9600);   
  init_encoder(); 
  init_PID();  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  Serial.println("Initialisation complete.");
}

void loop()
{
  Input = velocity;
  myPID.Compute();

  disp_values();

  dir = setpoint/abs(setpoint);
  
  if (dir == 1){
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    analogWrite(ENA,Output);
  }
  
  else if (dir == -1){
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    analogWrite(ENA,Output);
  }
  if (COUNT > 100){
    COUNT = 0;
    setpoint += 0.1;
    Setpoint = abs(setpoint);
  }
  COUNT++;
  delay(100);
}
