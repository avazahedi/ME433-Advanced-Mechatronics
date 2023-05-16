from ulab import numpy as np # to get access to ulab numpy functions
import time

# dt = 1.0/100.0 # 100Hz
dt = 5.0/1024.0
t = np.arange(0.0, 5.0, dt) # for 5s

s = 4.0 * np.sin(2 * np.pi * 100 * t) + 0.25 * np.sin(2 * np.pi * 1000 * t) + np.sin(2 * np.pi * 500 * t)

for i, v in enumerate(s):
    print(v)
    time.sleep(0.02)
