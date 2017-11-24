import pygame
import sys
from extract import *

class rectangle(object):
  """docstring for rectangle"""
  def __init__(self, pos, d, colour):
    self.rect = pygame.rect.Rect((pos[0],pos[1],d,d))
    self.colour = colour
  def draw(self, pos,colour):
    pygame.draw.rect(screen,colour,self.rect)

def draw(screen,filename,r,d,offset_x,offset_y,threshold,index=0):
  raw_data = get_data("data/"+filename,1,threshold)
  index %= raw_data[1]
  print index
  bits_data = rgb_bit_data(raw_data)
  byte_data = rgb_byte_data(bits_data)
  board = board_data(byte_data,index)
  # print board[0]
  pos = ring_pos(r,d)
  for i in range(len(pos)):
    pygame.draw.rect(screen, board[0][i], pygame.Rect(offset_x+pos[i][0],offset_y+pos[i][1], d, d))
  pos = weekday_pos(0,0,d)
  for i in range(len(pos)):
    pygame.draw.rect(screen, board[2][i], pygame.Rect(offset_x+pos[i][0]-7*d,offset_y+pos[i][1]+offset_y/4, d, d))
  

def main(argv):
  """
  visual <filename> <width> <threshold>
  """
  pygame.init()
  width,height = eval(argv[2]),eval(argv[2])#720,720
  screen = pygame.display.set_mode((width, height))
  done = False
  
  # Add this somewhere after the event pumping and before the display.flip()
  screen.fill((50,50,50))
  index = 0
  print index
  draw(screen,argv[1],width/3,width/70,width/2, height/2,eval(argv[3]),index)  
  pygame.display.flip()

  while not done:
    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        done = True
      if pygame.key.get_pressed()[pygame.K_RIGHT]:
        index+=1
        draw(screen,argv[1],width/3,width/70,width/2, height/2,eval(argv[3]),index)  
        pygame.display.flip()

      if pygame.key.get_pressed()[pygame.K_LEFT]:
        index-=1
        draw(screen,argv[1],width/3,width/70,width/2, height/2,eval(argv[3]),index)  
        pygame.display.flip()

# if __name__ == '__main__':
#   main(sys.argv)
  