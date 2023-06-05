import serial
import time
import matplotlib as plt
import math
import numpy as np
import sensor
import kalm
import pathtracker
import drive_motor_control
file = serial.Serial(port="/dev/ttyACM1", baudrate = 115200)
file.flush()
drive_motor_control.controlCmd([90,90,90,90,0,0,0,0],file)
