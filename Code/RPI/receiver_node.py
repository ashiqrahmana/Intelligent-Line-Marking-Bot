import serial
import time
import matplotlib as plt
import math
import numpy as np
import sensor
import kalm
import pathtracker
import drive_motor_control
#import pyproj
#defining the necessary parameters
waypoint = [13,80,0]
prev_time = 0
dt = 0#GPS variables
"""
X_G = [[0],[0],[0],[0],[0],[0]] 
P_G = np.identity(6)

R_G = [[0.001,    0,     0,    0,    0,      0],
       [    0,0.001,     0,    0,    0,      0],
       [    0,    0,     0,    0,    0,      0],
       [    0,    0,     0,0.001,    0,      0],
       [    0,    0,     0,    0,0.001,      0],
       [    0,    0,     0,    0,    0,      0]] 

C_G = [[1, 0, 0, dt, 0,   0],
       [0, 1, 0,  0, dt,  0],
       [0, 0, 0,  0,  0,  0],
       [0, 0, 0,  1,  0,  0],
       [0, 0, 0,  0,  1,  0],
       [0, 0, 0,  0,  0,  0]]
#noise at prediction step
W_G= np.array([[1],[1],[1],[1],[1],[1]])*0

#noise at correction step
U_G = np.array([[1],[1],[1],[1],[1],[1]])*-5

#process covariance prematrix
V_G = np.array([[1],[1],[1],[1],[1],[1]])*-0.0095


#MPU variables
X_M = [[0],[0],[0],[0],[0],[0]] 
P_M = np.identity(6)

R_M = [[0, 0,     0,  0,  0,      0],
       [0, 0,     0,  0,  0,      0],
       [0, 0, 0.001,  0,  0,      0],
       [0, 0,     0,  0,  0,      0],
       [0, 0,     0,  0,  0,      0],
       [0, 0,     0,  0,  0,  0.001]] 

C_M = [[0, 0, 0,  0,  0,   0],
       [0, 0, 0,  0,  0,  0],
       [0, 0, 1,  0,  0, dt],
       [0, 0, 0,  0,  0,  0],
       [0, 0, 0,  0,  0,  0],
       [0, 0, 0,  0,  0,  1]]

#noise at prediction step
W_M = np.array([[1],[1],[1],[1],[1],[1]])*0

#noise at correction step
U_M = np.array([[0],[0],[1],[0],[0],[1]])*-0.0001

#process covariance prematrix
V_M = np.array([[1],[1],[1],[1],[1],[1]])*1
"""

X = [[0],[0],[0],[0],[0],[0]] 
Y = [[0],[0],[0],[0],[0],[0]] 

P = np.identity(6)

R = [[0.0000164964,            0,                    0,        0,        0,      0],
       [         0,0.00001106694,                    0,        0,        0,      0],
       [         0,            0, np.radians(3.856152),        0,        0,      0],
       [         0,            0,                    0,  0.43016,        0,      0],
       [         0,            0,                    0,        0,  0.27246,      0],
       [         0,            0,                    0,        0,        0,      0]] 

C = [[1, 0, 0, dt, 0,   0],
       [0, 1, 0,  0, dt,  0],
       [0, 0, 1,  0,  0,  dt],
       [0, 0, 0,  1,  0,  0],
       [0, 0, 0,  0,  1,  0],
       [0, 0, 0,  0,  0,  1]]
#noise at prediction step
W= np.array([[1],[1],[1],[1],[1],[1]])*0

#noise at correction step
U = np.array([[0.112542],[0.000073],[np.radians(108)],[-0.4892],[-0.1184],[0]])

#process covariance prematrix
V = np.array([[1],[1],[1],[1],[1],[1]])*-0.0095
waypoints = [[13.0125],[80.238888],[0]]
file = serial.Serial(port="/dev/ttyACM1",baudrate = 115200)
file.flush()
while True:
    file.write(b"begin!")
    ser = file.readline().decode("utf-8").rstrip()
    #--------------------------------------------------------------------------------------
    #mpu_index = ser.index("mg")
    #processing the sensor readings
    #ser_m = ser[0:mpu_index+1]
    #mpu_read = sensor.mpu(ser_m)
    #sensor.mpu(ser_m)
    
    #ser_g = ser[mpu_index+1:]
    #gps_read = sensor.gps(ser_g)
    #sensor.gps(ser_g)
    #------------------------------------------------------------------------
    sensor = ser.split("/")
    if len(sensor) > 1:
        for index,item in enumerate(sensor):
            Y[index] = float(item)
        np.matrix(Y)    
        curr_time = time.time()
        dt = curr_time - prev_time
        dt = round(dt,2)
        prev_time = curr_time
        #print([[gps_read[0]],[gps_read[1]],[gps_read[2]],[mpu_read[0]],[mpu_read[1]],[mpu_read[2]],[dt]])
        
        Y[2] = np.radians(Y[2])
        Y[5] = np.radians(Y[5])
        print("Sensor Output = ",Y)
        X,P = kalm.kalman(Y,R,dt,X,P,U,V,W,C)
        np.set_printoptions(formatter={'float_kind':'{:f}'.format})
        print("Kalman Filter Output = ",X[0])
        D = X[0]
        #obtaining the the necessary parameters
        steer,trigger = pathtracker.cal_steering_angle(D[0:3], waypoint,0.25)
        #print("\tsteering_angle=\t",np.round(np.degrees(steering_angle),4))
        wb = 250 #w0heel base
        tw = 100 #track width
        v = 0.25 #velocity at reference
        #steer = np.radians(-100)
        tur_rad =(wb/np.tan(steer))
        pres_w = v/tur_rad
      
        steercmd1 = 90 + int(np.degrees(np.arctan(wb/(tur_rad-(tw/2)))))
        steercmd2 = 90 + int(np.degrees(np.arctan(wb/(tur_rad+(tw/2)))))
        steercmd3 = 90
        steercmd4 = 90
        const = 60*1000/(2*np.pi)
        rmcscmd1 = pres_w * (np.sqrt(pow(wb,2)+pow(tur_rad-50,2))*const)
        rmcscmd2 = pres_w * (np.sqrt(pow(wb,2)+pow(tur_rad+50,2))*const)
        rmcscmd3 = abs((pres_w) * (tur_rad+50)*const)
        rmcscmd4 = abs((pres_w) * (tur_rad-50)*const)
        #print(pres_w)
        if trigger == 1:
            drive_motor_control.controlCmd([steercmd1,steercmd2,steercmd3,steercmd4,rmcscmd1,rmcscmd2,rmcscmd3,rmcscmd4],file)

        else:
            drive_motor_control.controlCmd([90,90,90,90,0,0,0,0],file)

        """
        if X_M[0] == 0 and X_G[0] == 0:
            X_M = [[gps_read[0],gps_read[1],mpu_read[0],gps_read[2],gps_read[3],mpu_read[1]]
            X_G = [[gps_read[0],gps_read[1],mpu_read[0],gps_read[2],gps_read[3],mpu_read[1]]
                   
        #implementing kalman filter for mpu and gps seperately
        Y_G = [[gps_read[0]],[gps_read[1]],[0],[gps_read[2]],[gps_read[3]],[0]]
        X_G,P_G = kalman(Y_G,R_G,dt,X_G,P_G,U_G,V_G,W_G)
        
        Y_M = [[0],[0],[mpu_read[0]],[0],[0],[mpu_read[1]]]
        X_M,P_M= kalman(Y_M,R_M,dt,X_M,P_M,U_M,V_M,W_M)
        
        #fusing the two sensors 
        estimate = fusion_center(gps_est,mpu_est)
        
        #obtaining the the necessary parameters
        steering_angle,velocity = pure_pursuit_planner(estimate[0:3], waypoint)
        #sending the commands to the mega
        file.print([steering_angle,velocity])
        """
    else:
        print(ser)