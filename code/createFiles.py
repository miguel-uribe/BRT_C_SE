# %%
# Creating the service definition file

import numpy as np
import pandas as pd
import os
from route_conf import *
import matplotlib.pyplot as plt
import seaborn as sns
# this script creates the lane availability files for the 6 possible different configurations
#%%
#########################################################
##### THE CONFIGURATION FILES FOR CARS IN THE MAIN HIGHWAY
#########################################################
# The gradient should be given in meters
#confname = "3_2_returns_%d_%d"%(grad1,grad2) # the configuration name
# now we set the allowed lane changes
# LNA: Lane not available, this is to close lanes
# 0, the code, 1, the lane, 2, the position (in m) where the lane first becomes unavailable, 3, the position (in m) where the lane last is unavailable
# LSB: This is a separator that forbids the change between lanes
# 0, the code, 1, the lane with the separator to the left, 2, the position where the separator first appears, 3, the position where the separator last appears
# LSL: This is a separator that forbids the change to the left
# 0, the code, 1, the lane with the separator to the left, 2, the position where the separator first appears, 3, the position where the separator last appears
# LSR: This is a separator that forbids the change to the right
# 0, the code, 1, the lane with the separator to the right, 2, the position where the separator first appears, 3, the position where the separator last appears
# VM: The maximal speed rule
# 0, the code, 1, the lane for which the speed applies, 3, the initial position where the speed applies, 4, the final position where the speed applies, 5, the speed
for wagon in np.arange(6):

    confname = 'wagon_%d'%wagon

    LCR = []
    # to the north
    LCR.append(['LNA', 1, 0, dL])
    LCR.append(['LNA', 0, (wN[wagon]-dW), (wN[wagon]+dA)])
    LCR.append(['LNA', 1, dL+sL, L])
    # to the south
    LCR.append(['LNA', 1, L, L+dL])
    LCR.append(['LNA', 1, L+dL+sL, 2*L])
    LCR.append(['LNA', 0, (wN[wagon+6]-dW), (wN[wagon+6]+dA)])

    # avoiding changes to the stopping lane after returning to the main lane
    LCR.append(['LSL', 0, wN[wagon], dL+sL])
    LCR.append(['LSL', 0, wN[wagon+6], L+dL+sL])

    # avoiding returns to the main lane before stopping
    LCR.append(['LSR',1,dL,wN[wagon]])
    LCR.append(['LSR',1,L+dL,wN[wagon+6]])


    # creating the lane availability file, this is 0 when a lane is not available and 1 when the lane is available
    lanes = np.ones((2*L,Nmax))   # by default, all lanes are available among all the corridor
    # correcting for the information provided in route_conf
    for rule in LCR:
        if rule[0]=='LNA':
            lanes[round(rule[2]/Dx):round(rule[3]/Dx)+1,rule[1]] = 0

    # creating the maximal speed file, this is a number with the information regarding the maximal speed per lane and per position
    V = (vmax*Dt/Dx)*np.ones((2*L,Nmax))  # by default the maximal speed is the same along the entire corridor
    # now we chech for possible maximal speed rules
    for rule in LCR:
        if rule[0]=='VM':
            V[round(rule[2]/Dx):round(rule[3]/Dx)+1,rule[1]] = rule[4]*Dt/Dx

    # Now we create the leftchange file, containing the information regarding the posibility to change the lane to the left, this is increasing the lane. 0 means change is not possible, 1 means change is possible
    LC = np.copy(lanes)
    # clearly for the leftmost lane it is always impossible to move to the left
    LC[:,-1]=0
    # in addition, it is impossible to move to the left when the lane in the left is not there
    mask = lanes-np.roll(lanes, -1, axis = 1)==1
    LC[mask] = 0

    # Now we create the rightchange file, containing the information regarding the posibility to change the lane to the right, this is decreasing the lane. 0 means change is not possible, 1 means change is possible
    RC = np.copy(lanes)
    # clearly for the rightmost lane it is always impossible to move to the left
    RC[:,0]=0
    # in addition, it is impossible to move to the left when the lane in the left is not there
    mask = np.where(lanes-np.roll(lanes, 1, axis = 1)==1)
    RC[mask] = 0
    
    # now we check for possible special lane changing arrangements
    for rule in LCR:
        if rule[0]=='LSB':
            LC[round(rule[2]/Dx):round(rule[3]/Dx)+1,rule[1]] = 0
            RC[round(rule[2]/Dx):round(rule[3]/Dx)+1,rule[1]+1] = 0
        if rule[0]=='LSR':
            RC[round(rule[2]/Dx):round(rule[3]/Dx)+1,rule[1]] = 0
        if rule[0]=='LSL':
            LC[round(rule[2]/Dx):round(rule[3]/Dx)+1,rule[1]] = 0

    # Finally we create the endoflane where a number marks the distance to the end of the lane, by default this is set as 1000

    EL = 1000*np.ones((2*L,Nmax))
    auxEL = np.zeros((2*L,Nmax))
    mask =  (np.roll(lanes, 1, axis = 0) - lanes) == 1
    auxEL[mask] = 1

    for i in range(Nmax):
        endF = False
        for j in np.arange(2*L-1,-1,-1):
            if endF:
                EL[j,i] = endPos-j
            if auxEL[j,i] == 1:
                endF = True
                endPos = j - 1



    # Exporting the information
    dirname = os.path.dirname(__file__)
    file = os.path.join(dirname,"../conf/lanes_"+confname+".txt")
    np.savetxt(file,lanes, fmt ='%d')  # the lane availability
    file = os.path.join(dirname,"../conf/LC_"+confname+".txt")
    np.savetxt(file,LC, fmt ='%d')  # the left change
    file = os.path.join(dirname,"../conf/RC_"+confname+".txt")
    np.savetxt(file,RC, fmt ='%d')  # the left change
    file = os.path.join(dirname,"../conf/EL_"+confname+".txt")
    np.savetxt(file,EL, fmt ='%d')  # the left change
    #fig, ax = plt.subplots(1,1, figsize=(4,10))
    #sns.heatmap(RC)
file = os.path.join(dirname,"../conf/V.txt")
np.savetxt(file,V, fmt ='%d')  # the speed


initST = np.around((np.where(lanes[:,1]-np.roll(lanes[:,1], 1)==1)[0])/Dx).astype(int)
endST =np.around((np.where(lanes[:,1]-np.roll(lanes[:,1], 1)==-1)[0])/Dx).astype(int)
print(initST)
print(endST)

# %%
# Creating a file with the definition of all stops in the system
stop_definition = ['Calle_100_N', 'Calle_100_S']

text = ""
for i, stop in enumerate(stop_definition):
    text = text + "%d "%i+ stop +"\n"
dirname = os.path.dirname(__file__)
filename = os.path.join(dirname,"../conf/stoplist.txt")
file = open(filename, "w")
file.write(text)
file.close()

# %%
# Creating a file with the list of all the available stops in the system

dirname = os.path.dirname(__file__)
filename = os.path.join(dirname,"../conf/stopdefinition.txt")
file = open(filename, "w")
text = '0'
for i in range(6):
    text = text +" %d %d"%(wN[i], (i)%2)
text = text + '\n1'
for i in range(6):
    text = text +" %d %d"%(wN[i+6], (i)%2)
file.write(text)
file.close()
# %%
# Creating a file with the configuration of each service:

serv_dict = {   '8N': [bL,L,initST[0],endST[0],{'Calle_100_N': np.random.choice(range(6))}],
                '8S': [bL+L,2*L,initST[1],endST[1],{'Calle_100_S': np.random.choice(range(6))}],
                'C50': [bL+L,2*L,initST[1],endST[1],{'Calle_100_S': np.random.choice(range(6))}],
                'D10': [bL+L,2*L,initST[1],endST[1],{'Calle_100_S': np.random.choice(range(6))}],
                'F14': [bL+L,2*L,initST[1],endST[1],{'Calle_100_S': np.random.choice(range(6))}],
                'G12': [bL+L,2*L,initST[1],endST[1],{'Calle_100_S': np.random.choice(range(6))}],
                'H13': [bL+L,2*L,initST[1],endST[1],{'Calle_100_S': np.random.choice(range(6))}],
                'B13': [bL,L,initST[0],endST[0],{'Calle_100_N': np.random.choice(range(6))}],
                'B71': [bL,L,initST[0],endST[0],{'Calle_100_N': np.random.choice(range(6))}],
                'B12': [bL,L,initST[0],endST[0],{'Calle_100_N': np.random.choice(range(6))}],
                'B14': [bL,L,initST[0],endST[0],{'Calle_100_N': np.random.choice(range(6))}],
                'B10': [bL,L,initST[0],endST[0],{'Calle_100_N': np.random.choice(range(6))}],
                'B50': [bL,L,initST[0],endST[0],{'Calle_100_N': np.random.choice(range(6))}],
                'GenS': [bL+L,2*L,initST[1],endST[1],{}],
                'GenN': [bL,L,initST[0],endST[0],{}]
             }

# We now print the file with the service list
text = ""
for i, service in enumerate(serv_dict.keys()):
    text = text + "%d "%i + service + "\n"
dirname = os.path.dirname(__file__)
filename = os.path.join(dirname,"../conf/servicelist.txt")
file = open(filename, "w")
file.write(text)
file.close()
    


# now we print the file with the service definition
text = ""
stoplist = pd.read_csv('../conf/stoplist.txt', names = ['ID', 'name'], sep = " ")
servicelist = pd.read_csv('../conf/servicelist.txt', names = ['ID', 'name'], sep = " ")
for service_name, stops in serv_dict.items():
    serviceID = servicelist[servicelist['name']==service_name]['ID'].values[0]
    text = text + "%d %d %d %d %d "%(serviceID,stops[0], stops[1], stops[2], stops[3])
    for stop_name, stID in stops[4].items():
        stopID = stoplist[stoplist['name']==stop_name]['ID'].values[0]
        text = text + "%d %d "%(stopID,stID)
    text = text + "\n"
dirname = os.path.dirname(__file__)
filename = os.path.join(dirname,"../conf/servicedefinition.txt")
file = open(filename, "w")
file.write(text)
file.close()

# %%
# Creating a file with the average line headways
dirname = os.path.dirname(__file__)
filename = os.path.join(dirname,"../conf/servicedata.txt")
file = open(filename, "w")
# the list of headways
headways = np.random.choice(np.arange(100, 1000, 1), size = len(serv_dict))
# the list of dwell times
dwelltimes = np.random.choice(np.arange(30, 50, 1), size = len(serv_dict))
# the list of headway dependent dwell time
dwelltimes2 = np.random.choice(np.arange(0.01, 0.1, 0.01), size = len(serv_dict))
# the list of headway dependent dwell time
widths = np.random.choice(np.arange(0.01, 0.2, 0.01), size = len(serv_dict))
# this list of biarticulated values
biart = np.random.choice([0,100], size = len(serv_dict))

text = ""
for i,_ in enumerate(serv_dict.keys()):
    text =text + "%d %d %d %f %f %d\n"%(i,headways[i], dwelltimes[i], dwelltimes2[i], widths[i], biart[i])

file.write(text)
file.close()
#np.savetxt(filename, np.hstack( (np.arange(len(serv_dict)).reshape(len(serv_dict),1),headways,dwelltimes, dwelltimes2, widths, biart)), fmt='%.4f')

# %%
