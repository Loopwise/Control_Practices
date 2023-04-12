import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

header = ['uC_timer', 'i', 'in_dac', 'in_real', 'out']
data = pd.read_csv('RC_Circuit/data.csv', sep=';',decimal='.')
data.columns.values[:] = header
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
data_f = pd.DataFrame(data_f.T,
                    columns=['time', 'input', 'output'])
data_f.to_csv('RC_Circuit/filtered_data.csv', index = False)

plt.plot(t, inp, 'black')
plt.plot(t, out, 'blue')
plt.plot(t, S, 'r--')

plt.show()