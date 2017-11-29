import pygame
import sys
from extract import *


class PygameDisplay(wx.Panel):
    def __init__(self, parent, ID):
        wx.Panel.__init__(self, parent, ID)
        self.parent = parent
        self.hwnd = self.GetHandle()
       
        self.size = self.GetSizeTuple()
        self.size_dirty = True
       
        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_TIMER, self.Update, self.timer)
        self.Bind(wx.EVT_SIZE, self.OnSize)
       
        self.fps = 60.0
        self.timespacing = 1000.0 / self.fps
        self.timer.Start(self.timespacing, False)
 
        self.linespacing = 5
        

    def Update(self, event):
        # Any update tasks would go here (moving sprites, advancing animation frames etc.)
        # Load the next data
        event.Skip()

    def Redraw(self):
        if self.size_dirty:
            self.screen = pygame.Surface(self.size, 0, 32)
            self.size_dirty = False

        self.screen.fill((0,0,0))

        w, h = self.screen.get_size()

        print self.filename
        print self.index
        print self.board
        draw(self.screen,self.filename,self.board,self.index,w/3,w/70,w/2,h/2,0.000001)
        
        s = pygame.image.tostring(self.screen, 'RGB')  # Convert the surface to an RGB string
        img = wx.ImageFromData(self.size[0], self.size[1], s)  # Load this string into a wx image
        bmp = wx.BitmapFromImage(img)  # Get the image in bitmap form
        dc = wx.ClientDC(self)  # Device context for drawing the bitmap
        dc.DrawBitmap(bmp, 0, 0, False)  # Blit the bitmap image to the display
        del dc
 
    def OnPaint(self, event):
        self.Redraw()
        event.Skip()  # Make sure the parent frame gets told to redraw as well
 
    def OnSize(self, event):
        self.size = self.GetSizeTuple()
        self.size_dirty = True
 
    def Kill(self, event):
        # Make sure Pygame can't be asked to redraw /before/ quitting by unbinding all methods which
        # call the Redraw() method
        # (Otherwise wx seems to call Draw between quitting Pygame and destroying the frame)
        # This may or may not be necessary now that Pygame is just drawing to surfaces
        self.Unbind(event = wx.EVT_PAINT, handler = self.OnPaint)
        self.Unbind(event = wx.EVT_TIMER, handler = self.Update, source = self.timer)





# def main(argv):
#   """
#   visual <filename> <width> <threshold>
#   """
#   pygame.init()
#   width,height = eval(argv[2]),eval(argv[2])#720,720
#   screen = pygame.display.set_mode((width, height))
#   done = False
  
#   # Add this somewhere after the event pumping and before the display.flip()
#   screen.fill((50,50,50))
#   index = 0
#   print index
#   draw(screen,argv[1],width/3,width/70,width/2, height/2,eval(argv[3]),index)  
#   pygame.display.flip()

#   while not done:
#     for event in pygame.event.get():
#       if event.type == pygame.QUIT:
#         done = True
#       if pygame.key.get_pressed()[pygame.K_RIGHT]:
#         index+=1
#         draw(screen,argv[1],width/3,width/70,width/2, height/2,eval(argv[3]),index)  
#         pygame.display.flip()

#       if pygame.key.get_pressed()[pygame.K_LEFT]:
#         index-=1
#         draw(screen,argv[1],width/3,width/70,width/2, height/2,eval(argv[3]),index)  
#         pygame.display.flip()

# if __name__ == '__main__':
#   main(sys.argv)
  