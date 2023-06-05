void serialInput(){
  if (Serial.available() > 0){  
      String rawString = Serial.readStringUntil('\n');
    //String rawString = String(Serial.read());
    String c = String(rawString[0]);
      //Serial.print("rawString  ");
      //Serial.println(rawString); 
    if(rawString[0] == '0' || rawString[0] == '1' || rawString[0] == '2' || rawString[0] == '3'){
      rawString.remove(0,1);
      requiredAngle = rawString.toInt();
      //dirn = 1 --> Front Left
      //dirn = 2 --> Front 
      //dirn = 3 --> Front Right
      if (dirn == 1){
        int offset = 29;  
        servo[0].write(90 - offset);
        servo[1].write(90 - offset);
        servo[2].write(90 + offset);
        servo[3].write(90 + offset);
      }
      
      else if (dirn == 2 || dirn == 3 ){
        int offset = 29;  
        servo[0].write(90 + offset);
        servo[1].write(90 + offset);
        servo[2].write(90 - offset);
        servo[3].write(90 - offset);
      }

      else{
        servo[c.toInt()].write(requiredAngle);
      }
        //Serial.println(requiredAngle);
   
    }
    else if (rawString[0] == '4' || rawString[0] == '5' || rawString[0] == '6' || rawString[0] == '7'){
      rawString.remove(0,1);
      requiredSpeed = rawString.toInt();
      // Turn on motors
        analogWrite(M1A[c.toInt()-4],requiredSpeed);//C
        analogWrite(M1B[c.toInt()-4],0);
        //Serial.println(requiredSpeed);
      }
  }
}
