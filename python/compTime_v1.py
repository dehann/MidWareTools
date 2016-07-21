#!/usr/bin/env python

import socket, struct, time, math, errno
import numpy as np
import threading
import json
from pylab import *
from collections import deque


def interpret_address(addrstr):
    '''interpret a IP:port string'''
    a = addrstr.split(':')
    a[1] = int(a[1])
    return tuple(a)

def cross(a, b):
  c = [a[1]*b[2] - a[2]*b[1],
       a[2]*b[0] - a[0]*b[2],
       a[0]*b[1] - a[1]*b[0]]
  return c

class uniqueTimCont(object):
  def __init__(self):
    self.name = "NONE"
    self.hist_len = 50
    self.history = deque(maxlen=self.hist_len)
    self.compTime = deque(maxlen=self.hist_len*3)
  
  def setName(self,n):
    self.name = n
  
  def getName(self):
    return self.name
  
  def getSize(self):
    return self.hist_len
  
  def addData(self,usage,comptime):
    #print "adding number", float(data)
    self.history.append(float(usage))
    self.compTime.append(float(comptime))
  
  def getXData(self):
    return range(len(self.history))
  
  def getYData(self):
    return self.history
  
  def getCompData(self):
    return self.compTime
  
  def getCompTidx(self):
    return range(len(self.compTime))


class udp_socket(object):
  '''a UDP socket'''
  def __init__(self, device, blocking=True, input=True):
    a = device.split(':')
    if len(a) != 2:
      print("UDP ports must be specified as host:port")
      sys.exit(1)
    self.port = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    if input:
      self.port.bind(("", int(a[1])))
      self.destination_addr = None
    else:
      self.destination_addr = (a[0], int(a[1]))
    if not blocking:
      self.port.setblocking(0)
    self.last_address = None
  
  def recv(self,n=1000):
    try:
        data, self.last_address = self.port.recvfrom(n)
    except socket.error as e:
      if e.errno in [ errno.EAGAIN, errno.EWOULDBLOCK ]:
        return ""
      raise
    return data

class getDataHandler(object):
  def __init__(self):
    self.udp_soc = udp_socket("127.0.0.1:9999")
    self.buf = ""
    self.fig = plt.figure()
    self.gs = GridSpec(2, 3)
    self.ax = []
    self.br = []
    self.pltHdl = []
    self.barHdl = []
    #self.ax2 = plt.subplot(self.gs[0, 1])
    #self.ax3 = plt.subplot(self.gs[0, 2])
    self.ctrs = []
    self.updCount = 0
  
  def plotAll(self):
    for i in range(len(self.ctrs)):
      self.pltHdl[i].set_xdata(self.ctrs[i].getXData())
      self.pltHdl[i].set_ydata(self.ctrs[i].getYData())
      self.ax[i].relim()
      self.ax[i].autoscale_view(scalex=False, scaley=True)
    for i in range(len(self.ctrs)):
      d = self.ctrs[i].getCompTidx()
      dd = self.ctrs[i].getCompData()
      j = 0
      for elem in dd:
        d[j] = elem
        j +=1
      self.br[i].cla()
      self.br[i].hist(d,20)
      for tick in self.br[i].xaxis.get_major_ticks():
        tick.label.set_fontsize(10) 
        tick.label.set_rotation('vertical')
    self.fig.canvas.draw()
    
  
  def parseData(self, udp_str):
    try:
      udp_dict = json.loads(str(udp_str))
      return udp_dict
    except:
      print "Error: unable to parse JSON string"
      print udp_str
  
  def addIndividual(self, di):
    self.ctrs.append(uniqueTimCont())
    idx = len(self.ctrs)-1
    self.ctrs[idx].setName(di["NAME"].upper())
    self.ctrs[idx].addData(di["USAGE"], di["COMPTIME"])
    self.ax.append(plt.subplot(self.gs[0, idx]))
    self.ax[idx].set_xlim(0,self.ctrs[idx].getSize())
    self.ax[idx].grid()
    self.ax[idx].set_title(str(di["NAME"].upper()))
    ph, = self.ax[idx].plot([0.0], [0.0], color='r', linewidth=2)
    self.pltHdl.append(ph)
    # also the bar graphs
    self.br.append(plt.subplot(self.gs[1, idx]))
    self.br[idx].grid()
    bh, = self.br[idx].bar([1.0],[0.0])# normed=1, facecolor='g', alpha=0.75)
    self.barHdl.append(bh)
  
  def identifyIdividuals(self,di):
    iters = len(self.ctrs)
    found = False
    for i in range(iters):
      if (di["NAME"].upper()==self.ctrs[i].getName()):
        found = True
        self.ctrs[i].addData(di["USAGE"], di["COMPTIME"])
    if not found:
      self.addIndividual(di)
  
  def updateMsg(self):
    buf = self.udp_soc.recv(1000)
    if len(buf)==0:
      return 
    self.buf += buf
    a = self.buf.split('\n')
    if len(a)<2:
      return
    toparse = a[0]
    self.buf = ""
    for i in range(len(a)-1):
      self.buf += a[i+1]
    udp_dict = self.parseData(toparse)
    #print "Received dict", udp_dict
    if not udp_dict["NAME"].upper() == "NONE":
      self.identifyIdividuals(udp_dict)
    self.updCount += 1
    if (self.updCount>=20):
      self.plotAll()
      self.updCount = 0
  
  def startTimer(self):
    #fig.canvas.mpl_connect('key_press_event', on_key_close_tcp)
    self.timer = self.fig.canvas.new_timer(interval=10)
    self.timer.add_callback(hdlr.updateMsg)
    self.timer.start()


hdlr = getDataHandler()



try:
  hdlr.startTimer()
  plt.show()
  #tlast = time.time()
  #while True:
  #  if time.time() - tlast >= 0.02:
  #    tlast = time.time()
  #    hdlr.update()
except KeyboardInterrupt:
  print "Closing Computation Time Visualization"

