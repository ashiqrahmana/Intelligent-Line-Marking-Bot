import numpy as np
import math
earth_radius = 6371000

def cal_dist(x_1,y_1,x_2,y_2,unit_conversion):
    #print("\tX1\t",x_1,"\tY1\t",y_1,"\tX2\t",x_2,"\tY2\t",y_2)
    #return np.sqrt((x_1-x_2)**2 + (y_1-y_2)**2)
    phi_1 = math.radians(y_1)
    phi_2 = math.radians(y_2)
    
    delta_phi = math.radians(y_2-y_1)
    delta_lambda = math.radians(x_2-x_1)
    
    a = math.sin(delta_phi / 2.0) ** 2 + math.cos(phi_1) * math.cos(phi_2) * math.sin(delta_lambda / 2.0) ** 2
    d = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    print("Distance = ",d*earth_radius)
    return d*earth_radius*unit_conversion
    
def cal_alpha(waypoints,curr_pos,phi):
    theta_1 = 0
    theta_2 = 0
    print("Calculating x = ")
    x = cal_dist(waypoints[0], waypoints[1], curr_pos[0], waypoints[1],1)
    print("Calculating y = ")
    y = cal_dist(waypoints[0], waypoints[1], waypoints[0], curr_pos[1],1)
    theta = np.arctan(y/x)
    pos_neg = theta/np.absolute(theta);
    #s = np.floor(np.rad2deg(np.absolute(phi))/360)
    #scale = pos_neg * np.deg2rad(360) * s
    scale = 0
    if waypoints[0] - curr_pos[0] > 0 and waypoints[1] - curr_pos[1] > 0:
        theta_1 = scale + theta;
        #theta_2 = theta_1 - np.deg2rad(360);
    
    elif waypoints[0] - curr_pos[0] < 0 and waypoints[1] - curr_pos[1] > 0:
        theta_1 = scale + np.deg2rad(180) - theta;
        #theta_2 = theta_1 - np.deg2rad(360);
            
    elif waypoints[0] - curr_pos[0] < 0 and waypoints[1] - curr_pos[1] < 0:
        theta_1 = scale + np.deg2rad(180) +  theta;
        #theta_2 = theta_1 - np.deg2rad(360);
            
    elif waypoints[0] - curr_pos[0] > 0 and waypoints[1] - curr_pos[1] < 0:
        theta_1 = scale  + np.deg2rad(360) -  theta;
        #theta_2 = theta_1 - np.deg2rad(360);
    alpha_1 = theta_1 - phi
    #alpha_2 = theta_2 - phi
    alpha = alpha_1
    print("\talpha\t",np.degrees(alpha),"\theta\t",np.degrees(theta_1),"\phi\t",np.degrees(phi))
    #if np.absolute(alpha_1) > np.absolute(alpha_2):
    #    alpha = alpha_2
    return alpha

def cal_steering_angle(curr_pos, waypoints,Vf):
    orientation = curr_pos[2]
    trigger = 0
    Lmin = 3
    range_ = 0.2
    L = 1
    max = np.radians(45)
    angle_zone = 0
    wheel_speed = Vf
    Kdd = cal_dist(waypoints[0],waypoints[2],curr_pos[1],curr_pos[2],1)/Vf
    if Kdd < 1 or Kdd > 10:
        Kdd = 1   
    alpha = cal_alpha(waypoints,curr_pos,orientation)    
    steer_angle = np.arctan(2*L*np.sin(alpha)/(Lmin + Kdd*Vf))
    if steer_angle > max:
        steer_angle = max
        
    elif steer_angle < -max:
        steer_angle = -max
    print("V\t",Vf,"\tK\t",Kdd,"\talpha\t",np.degrees(alpha),"\tSteer\t",np.degrees(steer_angle))
       
    dist = cal_dist(waypoints[0],waypoints[1],curr_pos[0],curr_pos[1],1)
    acting_zone = np.sqrt(2*np.square(range_))
    
    if np.abs(alpha) >= np.deg2rad(angle_zone):
        acting_zone = dist + 10
        #if(type == 0 and dist <= acting_zone and np.abs(alpha) >= np.deg2rad(1)):
    if(dist <= acting_zone):
        steer_angle = 90
        trigger = -1
        if alpha > 0:
            trigger = 1
            
    return steer_angle,trigger