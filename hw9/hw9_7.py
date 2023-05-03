import csv
import matplotlib.pyplot as plt 
import numpy as np

for file in ['sigA.csv', 'sigB.csv', 'sigC.csv', 'sigD.csv']:
    # read the data
    t = [] # column 0
    y = [] # column 1

    with open(file) as f:
        # open the csv file
        reader = csv.reader(f)
        for row in reader:
            # read the rows one by one
            t.append(float(row[0])) # leftmost column
            y.append(float(row[1])) # second column

    # FIR filter
    # w = [
    #     0.000000000000000000,
    #     0.000391085607900160,
    #     0.003353289830491750,
    #     -0.000000000000000003,
    #     -0.025737623466723879,
    #     -0.034606372223859476,
    #     0.072380599422168998,
    #     0.284176158482516983,
    #     0.400085724695010803,
    #     0.284176158482516983,
    #     0.072380599422169012,
    #     -0.034606372223859504,
    #     -0.025737623466723893,
    #     -0.000000000000000003,
    #     0.003353289830491754,
    #     0.000391085607900160,
    #     0.000000000000000000
    # ]
    # cutoff: 2000, bandwidth: 3000

    w = [
        -0.000000000000000001,
        0.000770977406202302,
        0.003370877384644346,
        0.008489177296694770,
        0.016888946309278233,
        0.028986974865348694,
        0.044472107928130784,
        0.062110397569825219,
        0.079830201215864635,
        0.095090212361773480,
        0.105438514610263726,
        0.109103226103947321,
        0.105438514610263726,
        0.095090212361773493,
        0.079830201215864635,
        0.062110397569825268,
        0.044472107928130791,
        0.028986974865348712,
        0.016888946309278247,
        0.008489177296694786,
        0.003370877384644348,
        0.000770977406202300,
        -0.000000000000000001
    ]
    # cutoff: 100, bandwidth: 2000

    x = len(w)
    f = []
    for i in range(len(y)):
        if i < x:   # skip first x data points
            f.append(0)
        else:
            sum = 0
            for j in range(1, x+1):
                sum += w[j-1]*y[i-j]
            f.append(sum)

    # FFT
    dt = t[1] - t[0]
    Fs = 1/dt # sample rate = 10000
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
    fig.suptitle(f'Data from signal {str(file)[3]} \nLow-pass FIR \nnum weights: {len(w)}, Cutoff freq: 2000, Bandwidth: 3000\n')
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