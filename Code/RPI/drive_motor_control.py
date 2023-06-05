"""import serial

with serial.Serial("/dev/ttyACM0",115200) as file:
    file.flushInput()
    file.flushOutput()
    while(True):                
        for i in range(4):
            userInputTowerServo=[]           #This stores the required speed for all tower servo motors        
            userInputTowerServo.append(input("Enter position of tower servo "+str(i)+" :\t"))  
            #The address of each motor is a hex number.
            #MSB of hex is 0-Tower Servo; 1-RMCS Servo
            #LSB of hex is motor number (1 to 4)
            v = bytes((str(i)+userInputTowerServo[0]+'n').encode("ascii"))
            file.write(v)
        
        for i in range(4):
            userInputRMCSServo=[]           #This stores the required speed for all rmcs servo motors
            userInputRMCSServo.append(input("Enter speed of RMCS servo "+str(i)+" :\t"))
            w = bytes((str(i+4)+userInputRMCSServo[0]+'n').encode("ascii"))
            file.write(w)
        
        #file.write(bytes((str(int(input("Enter a value:\t"))*90)+'\n').encode("utf-8")))
        """
import serial

def controlCmd(cmd,file):
        print("Printing the signals = ",cmd)        
        for i in range(4):
            userInputTowerServo=[]           #This stores the required speed for all tower servo motors        
            userInputTowerServo.append(str(cmd[i]))  
            #The address of each motor is a hex number.
            #MSB of hex is 0-Tower Servo; 1-RMCS Servo
            #LSB of hex is motor number (1 to 4)
            v = bytes((str(i)+userInputTowerServo[0]+'n').encode("ascii"))
            print(v)
            file.write(v)
        
        for i in range(4):
            userInputRMCSServo=[]           #This stores the required speed for all rmcs servo motors
            userInputRMCSServo.append(str(cmd[i+4]))
            w = bytes((str(i+4)+userInputRMCSServo[0]+'n').encode("ascii"))
            file.write(w)
