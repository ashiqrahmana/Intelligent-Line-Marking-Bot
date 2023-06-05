# -*- coding: utf-8 -*-
"""
Created on Fri Feb 26 22:16:33 2021

@author: admin
"""

import gspread
from oauth2client.service_account import ServiceAccountCredentials
import pandas as pd
#from pprint import pprint
scope  =["https://spreadsheets.google.com/feeds",'https://www.googleapis.com/auth/spreadsheets',"https://www.googleapis.com/auth/drive.file","https://www.googleapis.com/auth/drive"]
creds = ServiceAccountCredentials.from_json_keyfile_name('Haru.json', scope)
client = gspread.authorize(creds)
sheet = client.open("lmbot").sheet1
data = sheet.get_all_records() 
gc=gspread.authorize(creds)
sh=gc.open('lmbot').sheet1
a=len(sh.col_values(1))
#print('row count',end=' ')
a=a-1
#from openpyxl import load_workbook
#workbook = load_workbook('lmbot.xlsx')
#sheet = workbook.active
#row_count = sheet.max_row
#for i in range(row_count):
 #   row=sheet.cell(row=i, column=2).value
  #  print(row)
#rangeA1notation = "Sh!A1:R300"  # Please set the range using A1Notation.

#client = gspread.authorize(creds)
#spreadsheet = client.open_by_key(spreadsheetId)
#values = sheet.values_get(rangeA1notation)
#v = values['values']
#df = pd.DataFrame(v)
#print(df)

#worksheet = sheet.get_sheet_by_name('lmbot')

#for row_cells in worksheet.iter_rows():
    #for cell in row_cells:
       #print('%s: cell.value=%s' % (cell, cell.value) )
#x = sheet.cell(row=,2).value
#print(x)
#print(a)
#while (a<=len(data)):
#for i in range(a):
    #a=i
    #row=sheet.cell(row=2,col=2).value
    #row = sheet.row_values(i)
#print(row)
#print(len(data))
#a=len(data)
#for i in range(4):
#row_count = sheet.max_row
#for i in range(row_count):
   # print(sheet.cell(row=i, column=1).value)
#for r in range(1,sheet.row_count - 1):
   #row = sheet.row_values(r)
  #row = sheet.row_values(i) # Get a specific row
#col = sheet.col_values(1)  # Get a specific column
#cell = sheet.cell(1,2).value  # Get the value of a specific cell
#print(cell)
#print(row)
#lat_l=[]
#long_l=[]
#latitude_l=[1.000,2.000,7.000,7.800,9.888]
#longitude_l=[3.000,5.000,4.000,6.800,3.888]
#for i in range(4):
 
    #lat_l=latitude_l[i]
    #long_l=longitude_l[i]
#insertColumn=["lat_l","long_l"]
#insertRow = ["hello", 1]
#sheet.insert_rows(row,2)
#sheet.add_rows(6)
#sheet.delete_rows(4)
#for i in range(4):
 #   row=sheet.cell(i,2).value
  #  print(row)
for r in range(1,sheet.row_count - 1):
    longitude = sheet.cell(r,1).value
    latitude = sheet.cell(r,2).value
    print(latitude,longitude)
#numRows = sheet.row_count  # Get the number of rows in the sheet
#k = True
#print(numRows)
#for r in range(1,sheet.row_count - 1):
 #while  k == True:    
  #   sheet.update_cell(1,3," ")
   #  longitude = sheet.cell(r,1).value
    # latitude = sheet.cell(r,2).value
     #print(latitude,longitude)
     #sheet.update_cell(2,3,"Update")
     #if sheet.cell(2,4).value == "Done":
       # break
