import os

#300mhz
print "Current frequency: 300MHz"
os.system("cpufreq-set -f 300Mhz")
os.system("python fact.py")

print "\n"

#600mhz
print "Current frequency: 600MHz"
os.system("cpufreq-set -f 600Mhz")
#os.system("cpufreq-info")
os.system("python fact.py")

print "\n"

#800MHz
print "Current frequency: 800MHz"
os.system("cpufreq-set -f 800Mhz")
#os.system("cpufreq-info")
os.system("python fact.py")

print "\n"


#1000mhz
print "Current frequency: 1000MHz"
os.system("cpufreq-set -f 1000Mhz")
os.system("python fact.py")

print "\n"

os.system("cpufreq-set -f 300Mhz")

FACT

import sys,time
def Factorial():
    n = 100
    fact=1
    for i in range(1,n+1):
       fact=fact*i

start_time=time.time()
Factorial()
print "Time taken in fact.py: %s seconds" % (time.time()-start_time)

"""

__________________________________________________________________

OUTPUT
root@beaglebone:~/bbb# nano b1.py
root@beaglebone:~/bbb# nano fact.py
root@beaglebone:~/bbb# python b1.py
Current frequency: 300MHz
Time taken in fact.py: 0.000715970993042 seconds


Current Frequency: 600MHz
Time taken in fact.py: 0.000257015228271 seconds


Current Frequency: 800MHz
Time taken in fact.py: 0.000249147415161 seconds


Current Frequency: 600MHz
Time taken in fact.py: 0.000164985656738 seconds


root@beaglebone:~/bbb# 



import sys,time
def Factorial():
    n = 100
    fact=1
    for i in range(1,n+1):
       fact=fact*i

start_time=time.time()
Factorial()
print "Time taken in fact.py: %s seconds" % (time.time()-start_time)
"""
