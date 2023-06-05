// 512/360 = x/angle ==> angle = x*360/(512*4.8)
// angle/360 = dist / pi(D) 

const int enA = 2;
const int enB = 3;

const int IN1 = 4; 
const int IN2 = 5;
const int ENA = 6;

float distance = 0;
float prev_distance = 0;

float prev_ms = 0;

volatile bool A  = 0;
volatile bool B  = 0;

float GR = 0.004515*100; //diameter = 0.135m


int COUNT = 0;


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
      float velocity = (distance - prev_distance)/ (millis() - prev_ms);
      prev_distance = distance;    
      Serial.print(velocity);
      Serial.print("\t");
      Serial.print(distance);
      Serial.print("\t");
      Serial.println(COUNT);
      prev_ms = millis();
  }
}

void setup()
{
  Serial.begin(9600);   
  init_encoder(); 
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  Serial.println("Initialisation complete.");
}

bool dir = 0;

void loop()
{
  disp_values();
  if (dir == 1){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENA,COUNT++);
  }
  else if( dir == 0 ){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(ENA,COUNT++);
  }
  if (COUNT > 255){
    COUNT = 0;
    dir = !dir;
  }
  delay(100);
}
