import serial
with serial.Serial("/dev/ttyACM0",115200) as file:
    file.flushInput()
    file.flushOutput()
    while(True):
        data=str(input("Enter a value:\t"))+'\n'
        file.write(data.encode("ascii"))
