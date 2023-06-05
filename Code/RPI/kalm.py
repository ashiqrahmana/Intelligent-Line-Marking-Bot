# -*- coding: utf-8 -*-
"""
Created on Sat Feb 27 01:34:47 2021

@author: admin
"""

import numpy as np
import matplotlib.pyplot as plt

from numpy import genfromtxt
dt=1


def prediction(X_hat_t,P_t,A,Q_t):
    
      X_hat=A.dot(X_hat_t)
      P=np.diag(np.diag(A.dot(P_t).dot(A.transpose())))+Q_t
      return X_hat,P

def update(X_hat,P,Y_t,R_t,H_t):
    
      K = P.dot(H_t.transpose()).dot( np.linalg.inv ( H_t.dot(P).dot(H_t.transpose()) +R_t ) )  
      err = Y_t - X_hat
      X_t = X_hat + K.dot(err)  #X=X+K(Y-H)X
      P = np.eye(6) - K.dot(H_t).dot(P)
      return X_t, P
      
def kalman(Y,R,dt,X,P,U,V,W,C):
    #MEASUREMENTS FROM CSV FILE
    #measurmens = genfromtxt('haru.csv', delimiter=',',skip_header=1)


    #Transition matrix
    A=np.array([[1.0,   0,   0, dt,  0,  0],
                [  0, 1.0,   0,  0, dt,  0],
                [  0,   0, 1.0,  0,  0, dt],
                [  0,   0,   0,1.0,  0,  0],
                [  0,   0,   0,  0,1.0,  0],
                [  0,   0,   0,  0,  0,1.0]])
                 
    H = np.eye(6)
    #Process cov
    a = np.zeros((6,6))
    Q_t= [[0.0095,     0,    0,    0,    0,    0],
          [    0, 0.0095,    0,    0,    0,    0],
          [    0,     0,0.0095,    0,    0,    0],
          [    0,     0,    0,0.0095,    0,    0],
          [    0,     0,    0,    0,0.0095,    0],
          [    0,     0,    0,    0,    0,0.0095]]

    X_hat,P_hat= prediction(X,A,P,Q_t)
    #print("Prediction:")
    #print("X_hat_t:\n",X_hat,"\nP_t:\n",P,"\nY_t:\n",Y)
    #Z_t=measurmens[i].transpose()
    #Z_t=Z_t.reshape(Z_t.shape[0],1)
    #print(Z_t)
    #print(Z_t.shape)

    X_t,P_t=update(X_hat,P_hat,np.dot(Y,C) + U,R,H)
    #print("Update:\n")
    #print("X_t:\n",X_t,"\nP_t\n",P_t)

    X_hat = X_t
    P_hat = P
    return X_hat, P_hat

    """
    plt.plot(X_hat,Z_t,label="measurements")
    plt.plot(X_hat,X_t,label="estimate")

    plt.legend()    
    """
        

