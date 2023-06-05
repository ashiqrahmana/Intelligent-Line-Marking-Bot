//#include <Wire.h>
//#include "Adafruit_VL53L0X.h"
//#include <Servo.h>
//
//Adafruit_VL53L0X vl = Adafruit_VL53L0X();
//Servo myscanner;
//
//float pos = 0;
//const float Pi = 3.14159;
//
//void setup(){
//  myscanner.attach(9);
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
//  myscanner.write(pos);
//  //uint8_t range = vl.readRange();
//  //VL53L0X_RangingMeasurementData_t measure; 
//  //Serial.println(String(measure.RangeMilliMeter)+"p"+String((pos*Pi)/180)+"p"+String(pos));
//  delay(10);
//}
//
//  myscanner.write(0);
//  delay(1000);
//}
//-----------------------------------------------------------------------------------
//#include "Adafruit_VL53L0X.h"
//#include <Servo.h>
//
//Servo scanner;
//int pos = 0;
//float range;
//bool returningToZero;
//int s[19];
//int j;
//int i = 0;
//int c = 0;
//int dirn ;
//Adafruit_VL53L0X lox = Adafruit_VL53L0X();
//int countfl = 0;
//int countf = 0;
//int countfr = 0;
//
//void setup1() {
//  if (c==0)
//  {
//  Serial.begin(115200);
//  scanner.attach(9);
//  scanner.write(0);
//  // wait until serial port opens for native USB devices
//  while (! Serial) {
//    delay(1);
//  }
//  
//  Serial.println("Adafruit VL53L0X test");
//  if (!lox.begin()) {
//    Serial.println(F("Failed to boot VL53L0X"));
//    while(1);
//  }
//  // power 
//  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
//  c++;
//}}
///*bool objectDetected(float range)
//{
//  if (range < 40)
//  {
//    return 1;
//  } 
//  else {
//    return 0;
//  }
//}*/
//
///*void lidar(){
//  VL53L0X_RangingMeasurementData_t measure;
//    
//  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
//
// /*for (int i=0;i<19;i++)
// {
//  range = measure.RangeMilliMeter;
//  Serial.println(range); 
//  delay(200);
// }*/
///*for (int i = 0;i<19;i++)
//  { 
//    if (measure.RangeStatus != 4) {  // phase failures have incorrect data
//    range = measure.RangeMilliMeter;
//    if (range<40)
//      j = 1;
//    else
//      j = 0;   
//  } 
//  else {
//    Serial.println(" out of range ");
//    j = 0;
//  }
//    s[i]=j;
//    Serial.print("Range: ");
//    Serial.println(range);
//    Serial.print("j = ");
//    Serial.println(j);
//    Serial.print(" ");
//     
//    pos+=5;
//    scanner.write(pos);
//    delay(200);
//  }
//    
//  scanner.write(0);
//  pos = 0;*/
//  /*for (int i=0;i<19;i++)
//  {
//    Serial.print(" ");
//    Serial.print(s[i]);
//  }
//  Serial.println(" ");*/
// 
///*if(objectDetected(range))
//{ 
//  Serial.println(". Range: ");
//  Serial.println(range);
//  Serial.println(". Servo's angle: ");
//  Serial.println(pos);
//}
//else 
//{
//  if (pos < 90 && returningToZero == false)
//    {
//      scanner.write(pos);
//      pos += 5;
//      Serial.print("Searching for object. Servo's angle: ");
//      Serial.println(pos);
//      if (pos == 90)
//        returningToZero = true;
//    } else if (returningToZero == true) {
//      pos -= 5;
//      Serial.print("Searching for object. Servo's angle: ");
//      Serial.println(pos);
//      scanner.write(pos);
//      if (pos == 0)
//        returningToZero = false;
//    }
//  }
//  delay(100);*/
//
//
//
//int lidar() {
//  VL53L0X_RangingMeasurementData_t measure;
//    
//  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
//  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
//    range = measure.RangeMilliMeter;
//    if (range<40)
//      j = 1;
//    else
//      j = 0;   
//  } 
//  else {
//    Serial.println(" out of range ");
//    j = 0;
//  }
//    s[i]=j;
//    i++;
//    pos+=5;
//    scanner.write(pos);
//    Serial.println(range);
//    Serial.println(j);
//    delay(1000);
//    
//    if(i>18)
//    
//    {
//      for (int z=0;z<19;z++)
//    {
//      Serial.print(s[z]);
//      Serial.print(" ");
//      
//      for (int a=0;a<7;a++)
//        countfl+=s[a];
//      for (int a=7;a<13;a++)
//        countf+=s[a];
//      for (int a=13;a<19;a++)
//        countfr+=s[a];
//    } 
//         
//      dirn = countfl > countf ? ( countfl > countfr ? 1 : 3) : (countf > countfr ? 2 : 3) ;
//      if (countfl==0 && countf==0 && countfr==0)
//        dirn = 0;
//      i = 0;
//    pos = 0;
//    Serial.println(dirn);
//    scanner.write(pos);
//    }
//    
//    countfl=0;
//    countf=0;
//    countfr=0;
//
//    return dirn;
//}
