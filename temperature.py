#! /usr/bin/env python3
import matplotlib.pyplot as plt
import matplotlib.animation as anim
from matplotlib import style
import numpy as np
import time
import os

#print(plt.style.available)
#style.use('fivethirtyeight')
style.use('seaborn')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

fig.canvas.set_window_title("Temperature monitor")

def animate(i):
    graph_data = open('./data/example.txt', 'r').read()
    lines = graph_data.split('\n')
    xs = []
    ys = []
    for line in lines:
        if len(line) > 1:
            x, y = line.split(',')
            xs.append( float(x) )
            ys.append( float(y) )

    ax1.clear()
    ax1.plot(xs, ys)


x = [0.0, 0.0]
y =[0.0,0.0]
temp_min = 35.0
temp_max = 70.0
dt = 1.0
iterat2sec = int(20.0/dt)
plt.axis( [0.0, 20.0, temp_min, temp_max] )
    
def animate2(i):
    x[0] = x[1]
    y[0] = y[1]
    #string = "sensors | grep \"Core 0\" "
    string = "vcgencmd measure_temp"
    stream = os.popen(string)
    output = stream.read()
    #temp = float(output[16:20])
    temp = float(output[5:8])
    y[1] = temp
    x[1] = float(i+1)

    if x[1] > 20.0:
        plt.axis( [ (i-iterat2sec+1)*dt, (i + 1)*dt, temp_min, temp_max ]  )

    ax1.plot(x,y,"bo-")



#interval = 1000 is for 1000 milisecs
#ani = anim.FuncAnimation(fig, animate, interval=1000)
ani = anim.FuncAnimation(fig, animate2, interval=1000)
plt.show()
