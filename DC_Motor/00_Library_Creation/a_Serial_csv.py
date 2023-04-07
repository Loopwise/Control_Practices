import serial as ser
from time import time
import csv

Arduino = ser.Serial('COM13', 115200)
Arduino.write(b'a')
f = open('data.csv', 'w', newline='')
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