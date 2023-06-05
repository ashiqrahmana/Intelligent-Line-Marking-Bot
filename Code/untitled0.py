# -*- coding: utf-8 -*-
"""
Created on Tue Jan  5 19:13:02 2021

@author: Ashiqrahman
"""
"""
function [alpha,sign] = cal_alpha(waypoints,curr_pos,phi)
    sign = 1;
    R = [ cos(phi), sin(phi);
         -sin(phi), cos(phi)];
    p = [curr_pos(1);curr_pos(2)];
    dummy = [1;0];         
    ref_ = R*dummy+p;
    %now calculating the distnace vector
    dist_v = [curr_pos(1)-waypoints(1); curr_pos(2)-waypoints(2)];
    alpha = (dot(ref_,dist_v)/(norm(ref_) * norm(dist_v)));
    %alpha = deg2rad(atan2d(ref_(1)*dist_v(2)-ref_(2)*dist(1),ref_(1)*dist_v(1)+ref_(2)*dist_v(2)));
    %alpha = subspace(ref_,dist_v);
    %sqrt(sum(r.*r))
    if alpha < 0
        sign = -1;
    end
end
"""
import numpy as np
phi = 45

curr_pos = np.array([[-10],
                     [0]])

waypoints = np.array([[10],
                      [10]])

R = np.array([[ np.cos(phi), np.sin(phi)],
              [-np.sin(phi), np.cos(phi)]])

p = np.array([[1],
             [2]])

dummy = np.array([[1],
                  [0]])  

ref_ = np.dot(R,dummy) + p
print(ref_)
dist_v = curr_pos-waypoints
print(dist_v)
alpha = np.arccos(np.dot(ref_,dist_v)/(np.sqrt(sum(np.square(ref_))) * np.sqrt(sum(np.square(dist_v)))))
print(np.degrees(alpha))
