import serial as ser
import csv
import os

# Path Configuration
fullpath = os.path.dirname(__file__)
outfile = "data.csv"

path = lambda filename: os.path.join(fullpath, filename)

f = open(path(outfile), 'w', newline='')

Arduino = ser.Serial('COM4', 115200)

fs = 10 # Frecuencia de muestreo
tf = 80 # Tiempo final

N = tf*fs + 1 # Número de muestras
i = 0

print("Start")

while True:

    line = Arduino.readline().strip().decode('utf-8')
    line = line.split(',')
    print(line)
    writer = csv.writer(f, delimiter=';')
    writer.writerow(line)
    
    i += 1

    if i == N:
        break

f.close()
Arduino.close()