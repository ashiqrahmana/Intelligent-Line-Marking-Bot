// 512/360 = x/angle ==> angle = x*360/(512*4.8)
// angle/360 = dist / pi(D) 

#include <PID_v1.h>

//Define Variables we'll be connecting to

double Setpoint1,Setpoint2,Setpoint3,Setpoint4;
double Input1,Input2,Input3,Input4;
double Output1,Output2,Output3,Output4;
double setpoint[4];

//Specify the links and initial tuning parameters
double Kp[4] = {100,100,100,100};
double Ki[4] = {50,50,50,50};
double Kd[4] = {1,1,1,1};

PID PID1(&Input1, &Output1, &Setpoint1, Kp[0], Ki[0], Kd[0], DIRECT);
PID PID2(&Input2, &Output2, &Setpoint2, Kp[1], Ki[1], Kd[1], DIRECT);
PID PID3(&Input3, &Output3, &Setpoint3, Kp[2], Ki[2], Kd[2], DIRECT);
PID PID4(&Input4, &Output4, &Setpoint4, Kp[3], Ki[3], Kd[3], DIRECT);

const int enA[4] = {2,20,0,0};
const int enB[4] = {3,21,0,0};

const int M1A[4] = {8,10,0,0};
const int M1B[4] = {9,11,0,0};

float distance[4] = {0,0,0,0};
float prev_distance[4] = {0,0,0,0};
float velocity[4] = {0,0,0,0};

float prev_ms[4] = {0,0,0,0};

volatile bool A[4] = {0,0,0,0};
volatile bool B[4] = {0,0,0,0};

float GR = 0.50; //diameter = 0.135m

int COUNT[4] = {0,0,0,0};

int dir[4] = {0,0,0,0};

void enA1Update(){
  A[0] = !A[0];
  if (A[0] == 1){
    if (A[0] == B[0]){
      distance[0] += GR;
    }
    else if (A[0] != B[0]){
      distance[0] -= GR;
    }
  }
}

void enB1Update(){
  B[0] = !B[0];
}


void enA2Update(){
  A[1] = !A[1];
  if (A[1] == 1){
    if (A[1] == B[1]){
      distance[1] += GR;
    }
    else if (A[1] != B[1]){
      distance[1] -= GR;
    }
  }
}

void enB2Update(){
  B[1] = !B[1];
}


void enA3Update(){
  A[2] = !A[2];
  if (A[2] == 1){
    if (A[2] == B[2]){
      distance[2] += GR;
    }
    else if (A[2] != B[3]){
      distance[2] -= GR;
    }
  }
}

void enB3Update(){
  B[2] = !B[2];
}

void enA4Update(){
  A[3] = !A[3];
  if (A[3] == 1){
    if (A[3] == B[3]){
      distance[3] += GR;
    }
    else if (A[3] != B[3]){
      distance[3] -= GR;
    }
  }
}

void enB4Update(){
  B[3] = !B[3];
}
void init_encoder(int i){
  /* Setup the interrupt pin */
  // put your setup code here, to run once:
  pinMode(enA[i], INPUT);
  pinMode(enB[i], INPUT);
  digitalWrite(enA[i], HIGH);
  digitalWrite(enB[i], HIGH);
  
  if (i == 0){
    attachInterrupt(digitalPinToInterrupt(enA[i]), enA1Update, CHANGE);
    attachInterrupt(digitalPinToInterrupt(enB[i]), enB1Update, CHANGE);
  }
  
  else if (i == 1){
    attachInterrupt(digitalPinToInterrupt(enA[i]), enA2Update, CHANGE);
    attachInterrupt(digitalPinToInterrupt(enB[i]), enB2Update, CHANGE);
  }
  
  else if (i == 2){
    attachInterrupt(digitalPinToInterrupt(enA[i]), enA3Update, CHANGE);
    attachInterrupt(digitalPinToInterrupt(enB[i]), enB3Update, CHANGE);
  }
  
  else if (i == 3){
    attachInterrupt(digitalPinToInterrupt(enA[i]), enA3Update, CHANGE);
    attachInterrupt(digitalPinToInterrupt(enB[i]), enB3Update, CHANGE);
  }
}

void disp_values(int i){
  
  if (millis() > prev_ms[i]+5){
      velocity[i] = abs(distance[i] - prev_distance[i])/ (millis() - prev_ms[i]);
      prev_distance[i] = distance[i];    
      //Serial.print(velocity[i]*dir[i]);
      //Serial.print(",");
      //Serial.println(setpoint[i]);
      prev_ms[i] = millis();
  }
}

void init_PID(int i){
    setpoint[i] = -0.3;
    if (i == 0){
       Setpoint1 = abs(setpoint[i]);
       PID1.SetMode(AUTOMATIC);
    }
    else if (i == 1){
       Setpoint2 = abs(setpoint[i]);
       PID2.SetMode(AUTOMATIC);
    }    
    else if (i == 2){
       Setpoint3 = abs(setpoint[i]);
       PID3.SetMode(AUTOMATIC);
    }    
    else if (i == 3){
       Setpoint4 = abs(setpoint[i]);
       PID4.SetMode(AUTOMATIC);
    }    
}

void init_rmcs()
{
  Serial.begin(9600);

  for (int i = 0; i<2; i++){
    init_encoder(i); 
    init_PID(i);  
    pinMode(M1A[i], OUTPUT);
    pinMode(M1B[i], OUTPUT);
  }
  Serial.println("Initialisation complete.");
}

float rmcs_control(double Setpoint,int i)
{
  double Speed_;
  for (int i = 0; i<2; i++){
    if (i == 0){
      PID1.Compute();
      Input1 = velocity[i];
      Speed_ = Output1;
      Setpoint1 = Setpoint;
    }
    else if (i == 1){
      PID2.Compute();
      Input2 = velocity[i];
      Speed_ = Output2;
      Setpoint2 = Setpoint;
    }
    else if (i == 2){
      PID3.Compute();
      Input3 = velocity[i];
      Speed_ = Output3;
      Setpoint3 = Setpoint;
    }
    else if (i == 3){
      PID4.Compute();
      Input4 = velocity[i];
      Speed_ = Output4;
      Setpoint4 = Setpoint;
    }    
    disp_values(i);
  
    dir[i] = setpoint[i]/abs(setpoint[i]);
    
    if (dir[i] == 1){
      analogWrite(M1A[i],Speed_);//C
      analogWrite(M1B[i],0);
      //Serial.println("Clokwise");
    }
    else if (dir[i] == -1){
      analogWrite(M1A[i],0);     //AC
      analogWrite(M1B[i],Speed_);
      //Serial.println("Counter Clokwise");
    }
    if (COUNT[i] > 100){
      COUNT[i] = 0;
      setpoint[i] += 0.1;
    }
    if (i == 0){
       Setpoint1 = abs(setpoint[i]);
    }
    else if (i == 1){
       Setpoint2 = abs(setpoint[i]);
    }
    else if (i == 2){
       Setpoint3 = abs(setpoint[i]);
    }
    else if (i == 3){
       Setpoint4 = abs(setpoint[i]);
    }
    COUNT[i]++;
    delay(100);
  }
  Serial.println(String(velocity[0])+"  "+String(velocity[1])+"  "+String(Setpoint1)+"  "+String(Setpoint2));
}

void stop_motor(){

  digitalWrite(IN1[0],LOW);
  digitalWrite(IN2[0],LOW);
  
  digitalWrite(IN1[1],LOW);
  digitalWrite(IN2[1],LOW);
  
  digitalWrite(IN1[2],LOW);
  digitalWrite(IN2[2],LOW);
  
  digitalWrite(IN1[3],LOW);
  digitalWrite(IN2[3],LOW);
    
}
