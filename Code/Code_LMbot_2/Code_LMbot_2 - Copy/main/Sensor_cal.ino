void init_lidar(){
    Serial.println("Adafruit VL53L0X intialisation");
    if (!lox.begin()) {
     Serial.println(F("Failed to boot VL53L0X"));
     while(1);
    }
    // power 
    Serial.println(F("VL53L0X API Simple Ranging Established\n\n"));
}

int lidar()
{
  VL53L0X_RangingMeasurementData_t measure;
    
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
    
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    range = measure.RangeMilliMeter;
    if (range<40)
      l = 1;
    else
      l = 0;   
  } 
  else {
    //Serial.println(" out of range ");
    l = 0;
  }
    s[k]=l;
    k++;
    pos+=5;
    scanner.write(pos);
    //Serial.println(range);
    //Serial.println(l);
    delay(1000/19);
    if(k>18)
    {
      for (int z=0;z<19;z++)
    {
      //Serial.print(s[z]);
      //Serial.print(" ");
      
      for (int a=0;a<7;a++)
        countfl+=s[a];
      for (int a=7;a<13;a++)
        countf+=s[a];
      for (int a=13;a<19;a++)
        countfr+=s[a];
    } 
         
      dirn = countfl > countf ? ( countfl > countfr ? 1 : 3) : (countf > countfr ? 2 : 3) ;
      if (countfl==0 && countf==0 && countfr==0)
        dirn = 0;
    pos = 0;
    k=0;
    //Serial.println(dirn);
    scanner.write(pos);
    }
    
    countfl=0;
    countf=0;
    countfr=0;

    return dirn;
}
