#nchow24, 250725575  (Nicole Anne Chow)
#simulation of pollution flow in a 3 pond circuit

import graphics
import plotpoints
from graphics import*
from plotpoints import*

#user input
maxPollutant = float(input("Maximum amount of pollutant (L): "))
leakingRate = float(input("Leaking rate of pollutant (L/min): "))
minutes = int(input("Number of minutes to run simulation: "))
print("\n")  #asthetics during output

#starting time and pollution levels
time = 1
amount1 = 0
amount2 = 0
amount3 = 0
FLOW_RATE = 0.005

while time <= minutes:
    if maxPollutant > 0:
        pollutant = leakingRate
        maxPollutant = maxPollutant - pollutant
    else:
        pollutant = 0
    def main():
        global amount1
        global amount3
        amount1 = amount1 + FLOW_RATE*amount3 - FLOW_RATE*amount1 + pollutant
        return amount1
    #pond2 calculations
    def pond2():
        global amount1
        global amount2
        amount2 = amount2 + FLOW_RATE*amount1 - FLOW_RATE*amount2
        return amount2
    #pond3 calculations
    def pond3():
        global amount3
        global amount2
        amount3 = amount3 + FLOW_RATE*amount2 - FLOW_RATE*amount3
        return amount3
    main()
    pond2()
    pond3()
    #Print pollution details at 60min intervals
    if time%60 == 0:
        print("After " + str(time) + "min:")
        print("Pond Pollution Levels:")
        print("Pond 1: " + "%.3f" % amount1 + "L")
        print("Pond 2: " + "%.3f" % amount2 + "L")
        print("Pond 3: " + "%.3f" % amount3 + "L")
        print ("\n")
    #print final details
    if time == minutes:
        print("Simulation Duration: " + str(time) + "min")
        print("Final Pond Pollution Levels: ")
        print("Pond 1: " + "%.3f" % amount1 + "L")
        print("Pond 2: " + "%.3f" % amount2 + "L")
        print("Pond 3: " + "%.3f" % amount3 + "L")
    time = time +1

class GraphicsWindow :
    def __init__(self, width = 400, height = 400) :
        global TheMainWindow

def createGrid(canvas,maxx,maxy):
    half = 5
    canvas.drawLine(50, 50, 450, 50)
    canvas.drawLine(50, 50, 50, 450)
    canvas.drawLine(450,50,450,450)
    canvas.drawLine(50,450,450,450)
    # assumes 40 tick marks on grid in y direction .. 50 to 450 of canvas
    stepy = round(maxy/40)
    for y in range(0,maxy,stepy) :
        yy = round(y/maxy*400)
        canvas.drawLine(50-half,50+yy,50+half,50+yy)
    canvas.drawText(2,40,str(maxy))
    canvas.drawText(2,440,"  0")
    # assumes 40 tick marks on grid in y direction .. 50 to 450 of canvas
    stepx = round(maxx/40)
    for x in range(0,maxx,stepx):
        xx = round(x/maxx*400)
        canvas.drawLine(xx+50,450-half,xx+50,450+half)
    canvas.drawText(40,460," 0")
    canvas.drawText(420,460,str(maxx))

def drawDots(canvas,x,maxx,y,maxy,color):
    if (x < 0 or x > maxx or y < 0 or y > maxy):
        print("-- drawDots failed because of values out of range")
    else:
        # draw points
        xv = 50+round(400*x/maxx,0)
        yv = 495-(50+round(400*y/maxy,0))
        canvas.setColor(color)
        canvas.drawOval(xv,yv,7,7)

    drawDots()
    createGrid()

