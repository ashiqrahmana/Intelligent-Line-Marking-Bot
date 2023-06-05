# -*- coding: utf-8 -*-
"""
Created on Sat Dec 19 18:26:17 2020

@author: Ashiqrahman
"""

import gspread
from oauth2client.service_account import ServiceAccountCredentials


# use creds to create a client to interact with the Google Drive API
scope  =["https://spreadsheets.google.com/feeds",'https://www.googleapis.com/auth/spreadsheets',"https://www.googleapis.com/auth/drive.file","https://www.googleapis.com/auth/drive"]


creds = ServiceAccountCredentials.from_json_keyfile_name(r'C:\Users\Ashiqrahman\.spyder-py3\api\cred.json', scope)
client = gspread.authorize(creds)

# Find a workbook by name and open the first sheet
# Make sure you use the right name here.
sheet = client.open("waypoints_testing").sheet1
data = sheet.get_all_records()  # Get a list of all records

row = sheet.row_values(3)  # Get a specific row
col = sheet.col_values(3)  # Get a specific column
cell = sheet.cell(1,2).value  # Get the value of a specific cell

insertRow = ["hello", 5, "red", "blue"]
sheet.add_rows(4)  # Insert the list as a row at index 4

#sheet.update_cell(2,2, "CHANGED")  # Update one cell

numRows = sheet.row_count  # Get the number of rows in the sheet
k = True

while  k == True:    
    sheet.update_cell(2,3," ")
    longitude = sheet.cell(2,1).value
    latitude = sheet.cell(2,2).value
    print(latitude,longitude)
    sheet.update_cell(2,3,"Update")
    if sheet.cell(2,4).value == "Done":
        break
    
    