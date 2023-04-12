import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Path Configuration
fullpath = os.path.dirname(__file__)

infile = "data.csv"
outfile = "filtered_data.csv"

path = lambda filename: os.path.join(fullpath, filename)

# Load File
header = ['cpu_time', 'uC_time', 'pwm', 'vel']
data = pd.read_csv(path(infile), sep=';',decimal='.')
data.columns.values[:] = header
n = len(data)

# Vector charge
t = np.array(data['uC_time'])
inp = np.array(data['pwm']*130/1023)
out = np.array(data['vel'])

# Proceso de filtrado (Media Móvil Exponencial)
S = np.zeros(n)
alpha = 0.3 #0.3
for i in range(n):
    if i == 0:
        S[i] = out[0]
    else:
        S[i] = alpha*out[i] + (1-alpha)*S[i - 1]

# Guardamos Data Filtrada
data_f = np.array([t, inp, S])
data_f = pd.DataFrame(data_f.T,
                    columns=['time', 'input', 'output'])

data_f.to_csv(path(outfile), index = False)

# Ploteo
fig, axs = plt.subplots(2)
fig.suptitle('Data Unfiletered and Filtered')

# Unfiltered Data
axs[0].plot(t, inp)
axs[0].plot(t, out)

# Filtered Data
axs[1].plot(t, inp)
axs[1].plot(t, S)

plt.show()

plt.plot(t, inp)
plt.plot(t, out, 'r--')
plt.plot(t, S)

plt.show()