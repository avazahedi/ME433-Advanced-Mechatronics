import csv
import matplotlib.pyplot as plt 
import numpy as np

file = 'me433_hw11.csv'

# read the data
t = [] # column 0
y = [] # column 1

# with open('sigD.csv') as f:
with open(file) as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows one by one
        t.append(float(row[0])) # leftmost column
        y.append(float(row[1])) # second column

# FFT
dt = t[1] - t[0]
Fs = 1/dt
# Fs = 10000 # sample rate
Ts = 1.0/Fs; # sampling interval
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t,y,'b')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'b') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')

plt.show()