import Adafruit_BBIO.GPIO as GPIO
import time
GPIO.setup("P8_9",GPIO.OUT)
GPIO.setup("P8_10",GPIO.OUT)
GPIO.setup("P8_11",GPIO.OUT)
GPIO.setup("P8_14",GPIO.OUT)
GPIO.setup("P8_13",GPIO.OUT)
GPIO.setup("P8_12",GPIO.OUT)

while True:
        GPIO.output("P8_9",GPIO.HIGH) #1 red
        GPIO.output("P8_10",GPIO.LOW)
        GPIO.output("P8_11",GPIO.LOW)

        GPIO.output("P8_14",GPIO.HIGH) #2 green
        GPIO.output("P8_13",GPIO.LOW)
        GPIO.output("P8_12",GPIO.LOW)
        print("Red1 and Green2")
        time.sleep(5)


        GPIO.output("P8_13",GPIO.HIGH)#2y
        GPIO.output("P8_14",GPIO.LOW)
        GPIO.output("P8_12",GPIO.LOW)

        GPIO.output("P8_9",GPIO.HIGH)#1 r
        GPIO.output("P8_10",GPIO.LOW)
        GPIO.output("P8_11",GPIO.LOW)
        print("Red1 and Yellow2")
        time.sleep(5)

        GPIO.output("P8_11",GPIO.HIGH) #1 green
	GPIO.output("P8_9",GPIO.LOW)
        GPIO.output("P8_10",GPIO.LOW)


        GPIO.output("P8_12",GPIO.HIGH) #2r
        GPIO.output("P8_13",GPIO.LOW)
        GPIO.output("P8_14",GPIO.LOW)
        print("Green1 and Red2")
        time.sleep(5)

        GPIO.output("P8_10",GPIO.HIGH)#1y
        GPIO.output("P8_9",GPIO.LOW)
        GPIO.output("P8_11",GPIO.LOW)

        GPIO.output("P8_12",GPIO.HIGH) #2r
        GPIO.output("P8_13",GPIO.LOW)
        GPIO.output("P8_14",GPIO.LOW)
        print("Yellow1 and Red2")
        time.sleep(5)

