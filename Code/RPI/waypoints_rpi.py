# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import cv2
import numpy as np
import gmplot 
import pygsheets
import pandas as pd
gc = pygsheets.authorize(service_file='Haru.json')
df = pd.DataFrame()



gmap= gmplot.GoogleMapPlotter(12.986678,80.139938,18)

# use creds to create a client to interact with the Google Drive API
##scope  =["https://spreadsheets.google.com/feeds",'https://www.googleapis.com/auth/spreadsheets',"https://www.googleapis.com/auth/drive.file","https://www.googleapis.com/auth/drive"]


##creds = ServiceAccountCredentials.from_json_keyfile_name(r'C:\Users\Ashiqrahman\.spyder-py3\api\cred.json', scope)
##client = gspread.authorize(creds)

# Find a workbook by name and open the first sheet
# Make sure you use the right name here.
##sheet = client.open("waypoints_testing").sheet1

resolution = 30
const = 180/(np.pi*6967410.324)
l = 10
b = 10
ref = [12.986678,80.139938]
# Create new blank 300x300 red image
width, height = l + 200, b + 200
# Create black blank image
image = np.zeros((height, width, 3), np.uint8)
white = (255,255,255)
x_1,y_1 =     10,   5
x_2,y_2 =   10+l,   5
x_3,y_3 =   10+l,   5+b
x_4,y_4 =     10,   5+b

image = cv2.line(image,(x_1+5,y_1),(x_2-5,y_2),white,1)
image = cv2.line(image,(x_2,y_2+5),(x_3,y_3-5),white,1)
image = cv2.line(image,(x_3-5,y_3),(x_4+5,y_4),white,1)
image = cv2.line(image,(x_4,y_4-5),(x_1,y_1+5),white,1)


img = image
img = img[0:height, 0:width]
edge = cv2.Canny(img, height, width)
contours, hierarchy = cv2.findContours(edge, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)


cv2.drawContours(img, contours[2], -1, (0,255,255), 3)

#print(len(contours[0]),len(contours[1]),len(contours[2]),len(contours[3]))
#print("contours")

#cv2.imshow("proceeced Image", img)
#cv2.imwrite('ground.jpg', image)
cv2.waitKey(0)

cv2.destroyAllWindows()
waypoints = np.zeros((4,1,2))

a=[]
for i in range(len(contours)):
    x = []
    arr = np.array(contours[i])
    arr.flatten()
    for j in range(len(arr)):
        if j%(resolution) == 0:
            x.append(True)
        else : 
              x.append(False)   
    a.append(arr[x]) 
    
# applying filter    
for i in range(len(contours)):
    if i%2 == 0:
        b = False
    else:
        b = True
    a[i] = a[i].reshape(len(a[i]),-1)
    a[i] = np.array(sorted(a[i], key=lambda x: -x[0],reverse = b))*const
    
 
t_ = [ref[0]-a[3][0][0],ref[1]-a[3][0][1]] 

lattitude_l = []
longitude_l = [] 

#3102
b = [[],[],[],[]]
b[0] = a[3]
b[1] = a[1]
b[2] = a[0]
b[3] = a[2]

for i in range(len(b)):       
    for j in range(len(b[i])):
        #if sheet.cell(2,3).value == "Update":
        b[i][j][0] = np.round((b[i][j][0]+t_[0]),6)
        b[i][j][1] = np.round((b[i][j][1]+t_[1]),6)
        lattitude_l.append(np.round((b[i][j][0]+t_[0]),6))
        longitude_l.append(np.round((b[i][j][1]+t_[1]),6))

        #gmap.marker(b[i][j][0],b[i][j][1],'cornflowerblue', edge_width = 2.5)
        gmap.plot(lattitude_l,longitude_l,  
                   'red', edge_width = 2.5)
        gmap.marker(b[i][j][0],b[i][j][1],'blue', edge_width = 2.5)
        #sheet.update_cell(2,1, b[i][j][0])  # Update one cell
        #sheet.update_cell(2,2, b[i][j][1])  # Update one cell
print(lattitude_l,'haru',longitude_l,'kandhan')
gmap.draw( "C:\\Users\\admin\\Desktop\\map.html" )
print("Check the map bruh :>")
for i in range(4):
    #latttude_l=lattitude_l[i]
    #longtude_l=longitude_l[i]
    
    df['latitude'] =[lattitude_l[0],lattitude_l[1],lattitude_l[2],lattitude_l[3]]
    df['longitude']=[longitude_l[0],longitude_l[1],longitude_l[2],longitude_l[3]]
    #print(latttude_l)
#open the google spreaheet (where 'PY to Gsheet Test' is the name of my sheet)
sh = gc.open('lmbot')

#select the first sheet 
wks = sh[0]

#update the first sheet with df, starting at cell B2. 
wks.set_dataframe(df,(1,1))


