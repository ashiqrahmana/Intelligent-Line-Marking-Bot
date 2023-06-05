import serial
import time
import matplotlib as plt
import math
import numpy
"""
i = 0
file = serial.Serial(port="/dev/ttyACM1", baudrate = 115200)
file.flush()
while True:
    file.write(b"begin!")
    ser = file.readline().decode("utf-8").rstrip()
    ser = ser[1:-2] #removing the characters like m
    ser = ser.split("/")
    if len(ser) == 3:
        pitch = float(ser[0])
        roll = float(ser[1])
        yaw = float(ser[2])
        print(pitch,roll,yaw)

    i+=1
"""
def mpu(ser): 
    ser = ser[1:-2] #removing the characters like m
    ser = ser.split("/")
    #print(ser)
    return ser
def gps(ser): 
    ser = ser[1:-2] #removing the characters like m
    ser = ser.split("/")
    #print(ser)
    return ser