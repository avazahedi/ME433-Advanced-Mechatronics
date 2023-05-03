import csv
import matplotlib.pyplot as plt 
import numpy as np

for file in ['sigA.csv', 'sigB.csv', 'sigC.csv', 'sigD.csv']:
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

    # moving average filter - x pts
    x = 100
    f = []
    for i in range(len(y)):
        if i < x:   # skip first x data points
            f.append(0)
        else:
            sum = 0
            for j in range(1, x+1):
                sum += y[i-j]
            f.append(sum/x)

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

    # FFT for filtered data
    F = np.fft.fft(f)/n # fft computing and normalization for filtered data
    F = F[range(int(n/2))]


    fig, (ax1, ax2) = plt.subplots(2, 1)
    fig.suptitle(f'Data from signal {str(file)[3]}, averaging {x} data points')
    ax1.plot(t,y,'k')
    ax1.set_xlabel('Time')
    ax1.set_ylabel('Amplitude')
    ax2.loglog(frq,abs(Y),'k') # plotting the fft
    ax2.set_xlabel('Freq (Hz)')
    ax2.set_ylabel('|Y(freq)|')

    # plotting filtered data
    ax1.plot(t,f,'r') # plotting the filtered data
    ax2.loglog(frq,abs(F),'r') # plotting the fft for the filtered data

    plt.show()