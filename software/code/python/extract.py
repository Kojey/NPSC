#!/usr/bin/env python
import wx
import math
"""
Extract rgb data information from Salea logic extracted waveform file
"""

def get_data(file,start,threshold=0.000005):
  """
  Convert Salea extracted data into useful waveform data
  Usage:  get_data(file_name)
  """
  data,pos = [],[]
  with open(file) as f: lines = [line.rstrip('\n') for line in f]
  for l in lines:
    data.append(l.split(','))
  for i in range(1,len(data)-1):
    e = eval(data[i+1][0])-eval(data[i][0])
    data[i].append(round(e*10**7,2))
    if abs(eval(data[i][0])-eval(data[i+1][0]))>threshold and eval(data[i+1][1])==start:
      pos.append(i+1)
  e = 0-eval(data[len(data)-1][0])  
  data[len(data)-1].append(round(e,2))
  data = data[pos[0]:]
  for i in range(len(pos)):
    pos[i]=pos[i] if(i<1) else int(math.floor(pos[i]/(2*24)))
  return [data,len(pos),min(data[0][2],data[1][2]),max(data[0][2],data[1][2])]    

def rgb_bit_data(data):
  """
  Convert Salea time data into binary rgb information
  """
  minimum,maximum = data[2],data[3]
  _data = []
  for x in range(0,len(data[0])-1,2):
    _data.append(0) if data[0][x][2]==minimum else _data.append(1)
  return _data

def rgb_byte_data(data):
  """
  Convert Salea data into rgb byte information
  """
  _data = []
  for i in range(0,len(data),24):
    g = bits_to_byte(data[i:i+8])
    r = bits_to_byte(data[i+8:i+16])
    b = bits_to_byte(data[i+16:i+24])
    _data.append([r,g,b])
  return _data

def board_data(data,pos):
  pos*=241
  return data[pos:pos+180],data[pos+180:pos+180+54],data[pos+180+54:]

def bits_to_byte(bits):
  number = 0
  for x in range(len(bits)):
    number += bits[x]*2**(7-x)
  return number

def ring_pos(r,d):
  pos = []
  for n in range(180):
    x = int((r+2*math.floor(n/60)*d)*math.cos(math.pi*n/30-math.pi/2))
    y = int((r+2*math.floor(n/60)*d)*math.sin(math.pi*n/30-math.pi/2))
    pos.append([x,y])#math.floor(x),math.floor(y)])
    # print int((r+2*math.floor(n/60)*d))
  # print pos
  return pos

def time_digit_pos():
  pass

def weekday_pos(x,y,d):
  pos = []
  for n in range(7):
    pos.append([x+2*n*d,y])
  return pos


# raw_data = get_data("data/data2.csv",1)
# bits_data = rgb_bit_data(raw_data)
# byte_data = rgb_byte_data(bits_data)
# board = board_data(byte_data)
# pos = ring_pos(100,2)
# print raw_data
# print pos
# pos = weekday_pos(0,0,2)
# print pos
