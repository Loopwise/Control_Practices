import serial as ser
from time import time
import csv

f = open('RC_Circuit/data_10hz.csv', 'w', newline='')

Arduino = ser.Serial('COM4', 115200)

start_time = time()
t = start_time

fs = 100 # Frecuencia de muestreo
tf = 40 # Tiempo final

N = tf*fs + 1 # Número de muestras
i = 0

print("Start")

while True:
    t = time()
    t_t = t - start_time

    line = Arduino.readline().strip().decode('utf-8')
    line = line.split(',')
    line = [round(t_t, 5)] + line
    print(line)
    writer = csv.writer(f, delimiter=';')
    writer.writerow(line)
    
    i += 1

    if i == N:
        break

f.close()
Arduino.close()