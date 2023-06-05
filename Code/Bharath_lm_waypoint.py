# -*- coding: utf-8 -*-
"""
Created on Thu Jun 17 14:04:55 2021

@author: techv
"""

#------------------------------------------------------------------------------
#-------------------------------------V2---------------------------------------
#------------------------------------------------------------------------------

import cv2
import numpy as np

l = 800
b = 400

ref = np.array([[10+200],[10+200]])
theta = np.radians(0)
R = np.array([[np.cos(theta), np.sin(theta)],[-np.sin(theta), np.cos(theta)]])

# Create new blank 300x300 red image
width, height = l + 1000, b + 500

# Create black blank image
image = np.zeros((height, width, 3), np.uint8)
white = (255,255,255)
p = np.array([[0]*2]*100)

#define the length and breadth
p[0][0],p[0][1] =   100  ,  50
p[1][0],p[1][1] =   100+l,   50
p[2][0],p[2][1] =   100+l,   50+b
p[3][0],p[3][1] =   100  ,   50+b

for ele in range(len(p)):
     temp = np.transpose(np.dot(R,np.transpose(p[ele]))+np.transpose(ref)) 
     p[ele][0] = temp[0]
     p[ele][1] = temp[1]
     
thickness = 3
image = cv2.line(image,(p[0][0],p[0][1]),(p[1][0],p[1][1]),white,thickness)
image = cv2.line(image,(p[1][0],p[1][1]),(p[2][0],p[2][1]),white,thickness)
image = cv2.line(image,(p[2][0],p[2][1]),(p[3][0],p[3][1]),white,thickness)
image = cv2.line(image,(p[3][0],p[3][1]),(p[0][0],p[0][1]),white,thickness)


# Center coordinates
center_coordinates = (120, 50)
 
# Radius of circle
radius = 20
  
# Blue color in BGR
color = (255, 0, 0)
  
# Line thickness of 2 px
thickness = 2
  
#image = cv2.circle(image, center_coordinates, radius, color, thickness)
# Using cv2.circle() method
# Draw a circle with blue line borders of thickness of 2 px
#image = cv2.circle(image, center_coordinates, radius, color, thickness)

# modify the data type
# setting to 32-bit floating point
#image = np.float32(image)
  
# apply the cv2.cornerHarris method
# to detect the corners with appropriate
# values as input parameters
#image =	cv2.cvtColor(image,	cv2.COLOR_BGR2GRAY)
"""image =	np.float32(image)
dest  =	cv2.cornerHarris(image,	2,	3,	0.04)
  
# Results are marked through the dilated corners
dest = cv2.dilate(dest, None)
#img[dst>0.01 *	dst.max()]   =	[0,	255, 255]
#print(image[dest > 0.01 * dest.max()])
#print(image)
cv2.imshow("processed Image", image)
#cv2.imwrite('ground.jpg', image)
cv2.waitKey(0)

image = cv2.add(image, dest)

cv2.imshow("processed Image", image)
#cv2.imwrite('ground.jpg', image)
cv2.waitKey(0)
"""

  
cv2.imshow("processed Image", image)
cv2.waitKey(0)

gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

kernel_size = 5
blur_gray = cv2.GaussianBlur(gray,(kernel_size, kernel_size),0)

low_threshold = 50
high_threshold = 150

edges = cv2.Canny(blur_gray, low_threshold, high_threshold)

contours, hierarchy = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)


#cv2.drawContours(image, contours, -1, (0,255,255), 3)

print(len(contours))
#print("contours")

cv2.imshow("processed Image", image)
#cv2.imwrite('ground.jpg', image)
cv2.waitKey(0)

cv2.destroyAllWindows()

rho = 1  # distance resolution in pixels of the Hough grid
theta = np.pi / 180  # angular resolution in radians of the Hough grid
threshold = 100  # minimum number of votes (intersections in Hough grid cell)
min_line_length = 100  # minimum number of pixels making up a line
max_line_gap = 20  # maximum gap in pixels between connectable line segments
line_image = np.copy(image) * 0  # creating a blank to draw lines on

# Run Hough on edge detected image
# Output "lines" is an array containing endpoints of detected line segments
lines = cv2.HoughLinesP(edges, rho, theta, threshold, np.array([]),
                    min_line_length, max_line_gap)


for line in lines:
    for x1,y1,x2,y2 in line:
        cv2.line(image,(x1,y1),(x2,y2),(255,0,0),5)
        print(x1,y1,x2,y2)
print(len(lines))  
cv2.imshow("processed Image", image)
cv2.waitKey(0)

cv2.destroyAllWindows()

