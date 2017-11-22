#!/usr/bin/env python
import wx

"""
Extract rgb data information from Salea logic extracted waveform file
"""

def get_data(file,start):
  """
  Convert Salea extracted data into useful waveform data
  Usage:  get_data(file_name)
  """
  threshold = 0.3
  data,pos = [],[]
  with open(file) as f: lines = [line.rstrip('\n') for line in f]
  for l in lines:
    data.append(l.split(','))
  for i in range(1,len(data)-1):
    e = eval(data[i+1][0])-eval(data[i][0])
    data[i].append(round(e*10**7,2))
    if abs(eval(data[i][0])-eval(data[i+1][0]))>threshold and eval(data[i+1][1])==start:
      pos.append(i+1)
  data = data[pos[0]:]
  return [data,pos,min(data[0][2],data[1][2]),max(data[0][2],data[1][2])]    

def rgb_bit_data(data):
  """
  Convert Salea time data into binary rgb information
  """
  minimum,maximum = data[2],data[3]
  _data = []
  # print data
  for x in range(0,len(data[0])-1,2):
    _data.append(0) if data[0][x][2]==minimum else _data.append(1)
  return _data

def rgb_byte_data(data):
  """
  Convert Salea data into rgb byte information
  """
  _data = []
  for i in range(0,len(data),24):
    r = bits_to_byte(data[i:i+8])
    g = bits_to_byte(data[i+8:i+16])
    b = bits_to_byte(data[i+16:i+24])
    _data.append([r,g,b])
  return _data

def board_data(data):
  return data[180],data[180:180+54],data[180+54:]

def bits_to_byte(bits):
  number = 0
  for x in range(len(bits)):
    number += bits[x]*2**(7-x)
  return number


raw_data = get_data("data/_data.csv",1)
bits_data = rgb_bit_data(raw_data)
byte_data = rgb_byte_data(bits_data)
board = board_data(byte_data)
print(board[2])
# print(rgb_bit_data(get_data("data/_data.csv",1)))
# print(bits_to_byte([0,0,0,0,1,1,1,1]))