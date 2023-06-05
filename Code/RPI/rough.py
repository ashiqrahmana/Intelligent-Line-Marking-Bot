import numpy as np
import math
earth_radius = 6371000
def cal_dist(x_1,y_1,x_2,y_2,unit_conversion):
    #return np.sqrt((x_1-x_2)**2 + (y_1-y_2)**2)
    dx = np.radians(x_1 - x_2)
    dy = np.radians(y_1 - y_2)
    a = math.sin(dy/2)**2 + math.cos(math.radians(y_2))*math.cos(math.radians(y_1))*math.sin(dx/2)**2
    print(a)
    d = 2*np.arctan2(np.sqrt(a),np.sqrt(1-a))
    print(d)
    return d*earth_radius*unit_conversion

print(cal_dist(1,1,2,2,1))