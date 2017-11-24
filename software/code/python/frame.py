# -*- coding: utf-8 -*- 

###########################################################################
## Python code generated with wxFormBuilder (version Nov 22 2017)
## http://www.wxformbuilder.org/
##
## PLEASE DO *NOT* EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc

###########################################################################
## Class Visual
###########################################################################

class Visual ( wx.Frame ):
	
	def __init__( self, parent ):
		wx.Frame.__init__( self, parent, id = wx.ID_ANY, title = wx.EmptyString, pos = wx.DefaultPosition, size = wx.Size( 600,650 ), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL )
		
		# self.SetSizeHints( wx.DefaultSize, wx.DefaultSize )
		
		bSizer15 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_panel = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 600,50 ), wx.TAB_TRAVERSAL )
		self.m_panel.SetMinSize( wx.Size( 600,50 ) )
		self.m_panel.SetMaxSize( wx.Size( 600,50 ) )
		
		bSizer16 = wx.BoxSizer( wx.HORIZONTAL )
		
		bSizer17 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_staticText17 = wx.StaticText( self.m_panel, wx.ID_ANY, u"Data", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTRE )
		self.m_staticText17.Wrap( -1 )
		bSizer17.Add( self.m_staticText17, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 5 )
		
		m_dataChoiceChoices = []
		self.m_dataChoice = wx.Choice( self.m_panel, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, m_dataChoiceChoices, 0 )
		self.m_dataChoice.SetSelection( 0 )
		bSizer17.Add( self.m_dataChoice, 0, wx.ALL, 5 )
		
		
		bSizer16.Add( bSizer17, 1, wx.EXPAND, 5 )
		
		bSizer18 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_stream = wx.StaticText( self.m_panel, wx.ID_ANY, u"Stream", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_stream.Wrap( -1 )
		bSizer18.Add( self.m_stream, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 5 )
		
		self.m_streamNumber = wx.StaticText( self.m_panel, wx.ID_ANY, u"-", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_streamNumber.Wrap( -1 )
		bSizer18.Add( self.m_streamNumber, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 5 )
		
		
		bSizer16.Add( bSizer18, 1, wx.EXPAND|wx.ALIGN_CENTER_VERTICAL, 5 )
		
		bSizer19 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_previous = wx.Button( self.m_panel, wx.ID_ANY, u"Previous", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer19.Add( self.m_previous, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 5 )
		
		self.m_next = wx.Button( self.m_panel, wx.ID_ANY, u"Next", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer19.Add( self.m_next, 0, wx.ALL|wx.ALIGN_CENTER_VERTICAL, 5 )
		
		
		bSizer16.Add( bSizer19, 1, wx.EXPAND, 5 )
		
		
		self.m_panel.SetSizer( bSizer16 )
		self.m_panel.Layout()
		bSizer15.Add( self.m_panel, 1, wx.EXPAND |wx.ALL, 5 )
		
		self.m_screen = wx.Panel( self, wx.ID_ANY, wx.DefaultPosition, wx.Size( 600,600 ), wx.TAB_TRAVERSAL )
		bSizer15.Add( self.m_screen, 1, wx.EXPAND |wx.ALL, 5 )
		
		
		self.SetSizer( bSizer15 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.m_dataChoice.Bind( wx.EVT_CHOICE, self.onData )
		self.m_previous.Bind( wx.EVT_BUTTON, self.onPrevious )
		self.m_next.Bind( wx.EVT_BUTTON, self.onNext )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def onData( self, event ):
		event.Skip()
	
	def onPrevious( self, event ):
		event.Skip()
	
	def onNext( self, event ):
		event.Skip()


# class App(wx.App):
#     def OnInit(self):
#         self.frame = Visual(parent = None)
#         self.frame.Show()
#         self.SetTopWindow(self.frame)
       
#         return True
 
# if __name__ == "__main__":
#     app = App()
#     app.MainLoop()
	

app = wx.App(False)

top = Visual(None)
top.Show()

app.MainLoop()