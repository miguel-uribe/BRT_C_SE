import numpy as np
Dt=1.0     # This is the time unit
Dx=1.0     # This is the space unit meters/cell
Db=[18,27]     # The car length, in m, articulated and biarticulated
vmax=17          # the default maximal speed, in m/s
acc = 1    # the acceleration in Dx/Dt^2
Nmax = 2  # the maximal number of lanes
Nparam = 18 # the number of parameters per bus
sL = 280 # the length of the station, in meters
dL = 1000 # The space before and after the station, in meters
L = 2*dL+sL # The total length of the system
dD = 17 # The distance between adjacent doors, in meters, not enough to allow a complete bus to park
dW = 45 # The end of the approximation zone
dA = 20 # The distance after the stop where a bus can return to the main lane
dDis = 100 # The position at the end of each corridor where buses disappear and appear
sN = np.array([54, 127, 204, L + 65, L + 142, L + 226]) # the position, from the origin of the station, of the first door in a wagon
wN = np.zeros(12)
wN[::2] = sN+dL
wN[1::2] = sN+dL+dD  # The array of stops





