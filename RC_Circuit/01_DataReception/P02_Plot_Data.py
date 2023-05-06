import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Path Configuration
fullpath = os.path.dirname(__file__)

infile = "data.csv"
outfile = "filtered_data.csv"

path = lambda filename: os.path.join(fullpath, filename)

# Data Load
header = ['i', 'in_real', 'out']
data = pd.read_csv(path(infile), sep=';',decimal='.', header = None, names = header)

n = len(data)

t = np.array(data['i'])
inp = np.array(data['in_real'])
out = np.array(data['out'])

# Filter
S = np.zeros(n)
alpha = 0.25
for i in range(n):
    if i == 0:
        S[i] =  out[i]
    else:
        S[i] = alpha*out[i] + (1 - alpha)*S[i - 1]

data_f = np.array([t, inp, S])
data_f = pd.DataFrame(data_f.T, columns=['time', 'input', 'output'])
data_f.to_csv(path(outfile), index = False)

plt.plot(t, inp, 'black')
plt.plot(t, out, 'blue')
plt.plot(t, S, 'r--')

plt.show()