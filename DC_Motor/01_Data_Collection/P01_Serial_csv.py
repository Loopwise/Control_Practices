import serial as ser
from time import time
import csv
import os

# Path Configuration
fullpath = os.path.dirname(__file__)
outfile = "data.csv"

path = lambda filename: os.path.join(fullpath, filename)

f = open(path(outfile), 'w', newline='')

# Serial configuration
Arduino = ser.Serial('COM13', 115200)
Arduino.write(b'a')

# Saving data
start_time = time()
t = start_time
i = 0
while True:
    t = time()
    t_t = t - start_time

    if t_t > 2.5*i:
        out = b'1023' if i%2 else b'0'
        Arduino.write(out)
        i += 1

    line = Arduino.readline().strip().decode('utf-8')
    line = line.split(',')
    line = [round(t_t, 5)] + line
    print(line)
    writer = csv.writer(f, delimiter=';')
    writer.writerow(line)
    
    if t_t > 10:
        break

f.close()
Arduino.close()