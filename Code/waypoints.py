# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

# #import cv2
# #import numpy as np

# #import gmplot 

# #import gspread
# #from oauth2client.service_account import ServiceAccountCredentials


# #gmap= gmplot.GoogleMapPlotter(12.986678,80.139938,18)

# # use creds to create a client to interact with the Google Drive API
# ##scope  =["https://spreadsheets.google.com/feeds",'https://www.googleapis.com/auth/spreadsheets',"https://www.googleapis.com/auth/drive.file","https://www.googleapis.com/auth/drive"]


# ##creds = ServiceAccountCredentials.from_json_keyfile_name(r'C:\Users\Ashiqrahman\.spyder-py3\api\cred.json', scope)
# ##client = gspread.authorize(creds)

# # Find a workbook by name and open the first sheet
# # Make sure you use the right name here.
# ##sheet = client.open("waypoints_testing").sheet1

# # Initiate FAST object with default values
# #fast = cv2.FastFeatureDetector_create()

# resolution = 30
# const = 180/(np.pi*6967410.324)
# l = 1000
# b = 500
# ref = [12.986678,80.139938]
# # Create new blank 300x300 red image
# width, height = l + 200, b + 200
# # Create black blank image
# image = np.zeros((height, width, 3), np.uint8)
# white = (255,255,255)
# x_1,y_1 =     10,   5
# x_2,y_2 =   10+l,   5
# x_3,y_3 =   10+l,   5+b
# x_4,y_4 =     10,   5+b

# image = cv2.line(image,(x_1,y_1),(x_2,y_2),white,5)
# image = cv2.line(image,(x_2,y_2),(x_3,y_3),white,5)
# image = cv2.line(image,(x_3,y_3),(x_4,y_4),white,5)
# image = cv2.line(image,(x_4,y_4),(x_1,y_1),white,5)

# # CONTOURS
# img = image
# img = img[0:height, 0:width]
# edge = cv2.Canny(img, height, width)
# contours, hierarchy = cv2.findContours(edge, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)


# #cv2.drawContours(img, contours[2], -1, (0,255,255), 3)

# #print(len(contours[0]),len(contours[1]),len(contours[2]),len(contours[3]))
# #print("contours")

# cv2.imshow("processed Image", img1)
# #cv2.imwrite('ground.jpg', image)
# cv2.waitKey(0)

# cv2.destroyAllWindows()

# waypoints = np.zeros((4,1,2))

# a=[]
# for i in range(len(contours)):
#     x = []
#     arr = np.array(contours[i])
#     arr.flatten()
#     for j in range(len(arr)):
#         if j%(resolution) == 0:
#             x.append(True)
#         else : 
#               x.append(False)   
#     a.append(arr[x]) 
    
# # applying filter    
# for i in range(len(contours)):
#     if i%2 == 0:
#         b = False
#     else:
#         b = True
#     a[i] = a[i].reshape(len(a[i]),-1)
#     a[i] = np.array(sorted(a[i], key=lambda x: -x[0],reverse = b))*const
    
 
# t_ = [ref[0]-a[3][0][0],ref[1]-a[3][0][1]] 

# lattitude_l = []
# longitude_l = [] 

# #3102
# b = [[],[],[],[]]
# b[0] = a[3]
# b[1] = a[1]
# b[2] = a[0]
# b[3] = a[2]

# for i in range(len(b)):       
#     for j in range(len(b[i])):
#         #if sheet.cell(2,3).value == "Update":
#         b[i][j][0] = np.round((b[i][j][0]+t_[0]),6)
#         b[i][j][1] = np.round((b[i][j][1]+t_[1]),6)
#         lattitude_l.append(np.round((b[i][j][0]+t_[0]),6))
#         longitude_l.append(np.round((b[i][j][1]+t_[1]),6))

#         #gmap.marker(b[i][j][0],b[i][j][1],'cornflowerblue', edge_width = 2.5)
# #        gmap.plot(lattitude_l,longitude_l,  
# #                   'red', edge_width = 2.5)
# #        gmap.marker(b[i][j][0],b[i][j][1],'blue', edge_width = 2.5)
#         #sheet.update_cell(2,1, b[i][j][0])  # Update one cell
#         #sheet.update_cell(2,2, b[i][j][1])  # Update one cell
# print(lattitude_l,longitude_l)
# #gmap.draw( "C:\\Users\\Ashiqrahman\\Desktop\\map.html" )
# #print("Check the map bruh :>")


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

radius = int(b/5)

#define the length and breadth
p[0][0] , p[0][1]   =       0, 0
p[1][0] , p[1][1]   =       l, 0
p[2][0] , p[2][1]   =       l, b
p[3][0] , p[3][1]   =       0, b
p[4][0] , p[4][1]   =     l/4, 0
p[5][0] , p[5][1]   =     l/4, b
p[6][0] , p[6][1]   =     l/2, 0
p[7][0] , p[7][1]   =     l/2, b
p[8][0] , p[8][1]   =   l*3/4, 0
p[9][0] , p[9][1]   =   l*3/4, b
p[10][0], p[10][1]  =   0    , b/2 - b/5 
p[11][0], p[11][1]  =   0    , b/2 + b/5
p[12][0], p[12][1]  =   l    , b/2 - b/5   
p[13][0], p[13][1]  =   l    , b/2 + b/5  

def quatercircle ( image, startAngle, endAngle, pnt):
    axes = (radius,radius)
    center = (pnt[0],pnt[1])
    angle = 0
    cv2.ellipse(image, center, axes, angle, startAngle, endAngle, white, thickness)


for ele in range(len(p)):
     temp = np.transpose(np.dot(R,np.transpose(p[ele]))+np.transpose(ref)) 
     p[ele][0] = temp[0]
     p[ele][1] = temp[1]
     
thickness = 3
image = cv2.line(image,(p[0][0],p[0][1]),(p[1][0],p[1][1]),white,thickness)
image = cv2.line(image,(p[1][0],p[1][1]),(p[2][0],p[2][1]),white,thickness)
image = cv2.line(image,(p[2][0],p[2][1]),(p[3][0],p[3][1]),white,thickness)
image = cv2.line(image,(p[3][0],p[3][1]),(p[0][0],p[0][1]),white,thickness)
image = cv2.line(image,(p[4][0],p[4][1]),(p[5][0],p[5][1]),white,thickness)
image = cv2.line(image,(p[6][0],p[6][1]),(p[7][0],p[7][1]),white,thickness)
image = cv2.line(image,(p[8][0],p[8][1]),(p[9][0],p[9][1]),white,thickness)

image = cv2.line(image,(p[10][0]+radius,p[10][1]),(p[11][0]+radius,p[11][1]),white,thickness)
image = cv2.line(image,(p[12][0]-radius,p[12][1]),(p[13][0]-radius,p[13][1]),white,thickness)

quatercircle ( image, 270, 360, p[10])
quatercircle ( image, 0, 90, p[11])
quatercircle ( image, 270, 180, p[12])
quatercircle ( image, 90, 180, p[13])

#Center coordinates
center_coordinates = (500, 500)
 
# Radius of circle
radius = 100
  
# Blue color in BGR
color = (255, 255, 255)
  
# Line thickness of 2 px
thickness = 2
  
# Using cv2.circle() method
# Draw a circle with blue line borders of thickness of 2 px
#image = cv2.circle(image, center_coordinates, radius, color, thickness)
  
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
        cv2.line(image,(x1,y1),(x2,y2),(255,0,0),2)
        print(x1,y1,x2,y2)
print(len(lines))  
cv2.imshow("processed Image", image)
cv2.waitKey(0)

cv2.destroyAllWindows()

