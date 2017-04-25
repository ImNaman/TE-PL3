import Adafruit_BBIO.GPIO as GPIO
import time
GPIO.setup("P8_16",GPIO.OUT) #redLight 1st Floor
GPIO.setup("P8_14",GPIO.OUT) #yellowLight 2ndFloor
GPIO.setup("P8_12",GPIO.OUT) #greenLight 3rd Floor

GPIO.setup("P8_13",GPIO.IN) #3rdFloor Button
GPIO.setup("P8_19",GPIO.IN) #2ndFloor Button
GPIO.setup("P8_18",GPIO.IN) #1stFloor Button

def redHigh():
        GPIO.output("P8_16", GPIO.HIGH)
def yellowHigh():
        GPIO.output("P8_14", GPIO.HIGH)
def greenHigh():
        GPIO.output("P8_12", GPIO.HIGH)
def redLow():
        GPIO.output("P8_16", GPIO.LOW)
def yellowLow():
        GPIO.output("P8_14", GPIO.LOW)
def greenLow():
        GPIO.output("P8_12", GPIO.LOW)
var = 1
while True:
        if GPIO.input("P8_18")==1:
                if var == 3:
                        print "Current floor=3"
                        greenLow()
                        yellowHigh()
                        print "Changed to 2"
                        time.sleep(2)
                        yellowLow()
						redHigh()
                        print "Current floor=1"
                var = 1

        elif GPIO.input("P8_19")==1:
                if var == 3:
                        print "Current floor=3"
                        greenLow()
                        yellowHigh()
                        print "Current floor=2"
                if var == 1:
                        print "Current floor=1"
                        redLow()
                        yellowHigh()
                        print "Current floor=2"
                var = 2

        elif GPIO.input("P8_13")==1:
                if var == 2:
                        print "Current floor=2"
                        yellowLow()
                        greenHigh()
                        print "Current floor=3"
                if var == 1:
                        print "Current floor=1"
                        redLow()
                        yellowHigh()
                        print "Current floor=2"
                        time.sleep(2)
						yellowLow()
                        greenHigh()
                        print "Current floor=3"
                var = 3

		
