/*
===============================================================================================================
QMC5883LCompass.h Library Azimuth Example Sketch
Learn more at [https://github.com/mprograms/QMC5883Compas]
===============================================================================================================
v0.3 - June 12, 2019
Written by MRPrograms 
Github: [https://github.com/mprograms/]

Release under the GNU General Public License v3
[https://www.gnu.org/licenses/gpl-3.0.en.html]
===============================================================================================================
*/
//-----------------------------------------------------------------------
//--------------------------Compass Test --------------------------------
//-----------------------------------------------------------------------

#include <QMC5883LCompass.h>

QMC5883LCompass compass;
float  timeout = 100*100,time_cal =  0.0, start_time = 0.0;
float  min_x = -100000, min_y = -100000, max_x = 100000, max_y = 100000, phi = 0.0;

void init_qmc() {
  //Serial.begin(9600);
  
  compass.init();
  compass.setMode(0x01, 0x0C, 0x00, 0x00);                  //Continuos, 200 Hz, 2G, 512 (MODE, ODR, RNG, OSR)
  compass.setCalibration ( -1090, 16, -1257, 0, -1, 1183);
  Serial.println("Rotate the sensor from 0 to 360");
  delay(1000);

  for(int i = 0; i < 4; i++){
    servo[i].write(90);  
  }
  
  analogWrite(M1A[0],0);
  analogWrite(M1B[0],255);

  analogWrite(M1A[1],255);
  analogWrite(M1B[1],0);

  analogWrite(M1A[2],255);
  analogWrite(M1B[2],0);

  analogWrite(M1A[3],0);
  analogWrite(M1B[3],255);
  
  delay(2000);
  
  float startTime = millis();
  
  while(timeout > time_cal){
      // Read compass values
       compass.read();
    
      // Return XYZ readings
      float x = compass.getX();
      float y = compass.getY();
      if(x > min_x)
        min_x = x;
      if(x < max_x)
        max_x = x; 
      if(y > min_y)
        min_y = y;
      if(y < max_y)
        max_y = y;
        
     Serial.println(String(max_x)+String("\t")+String(max_y)+String("\t")+String(min_x)+String("\t")+String(min_y)+String("\t"));
     time_cal = millis() - start_time;       
  }
  stop_motor();
  delay(2000);
}

float getPhi() {

  // Read compass values

  compass.read();
  
  // Return XYZ readings
  float map_x = map(compass.getX(),min_x,max_x,  255,-255);
  float map_y = map(compass.getY(),min_y,max_y, -255, 255);
  float mag = sqrt(pow(map_x,2) + pow(map_y,2));
  //float theta = radians(90);
  //map_x =  map_x*(0) + map_y*(1);
  //map_y =  map_x*(-1) + map_y*(0);
  
  phi = degrees(acos(abs(map_y)/mag));
  //second quadrant
  if (map_x > 0 && map_y > 0){
     phi = 180.0 - phi;
  }
  //Third quadrant
  else if (map_x < 0 && map_y > 0){
     phi = 180.0 + phi;
  }
  //Fourth Quadrant
  else if (map_x < 0 && map_y < 0){
     phi = 360 - phi;
  }
  //Serial.print(map_x);Serial.print("\t");Serial.print(map_y);Serial.print("\t");Serial.println(phi);
  return phi ; 
}
