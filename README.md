# BRT_C_SE
C++ and Python programming scheme to simulate and optimize the behaviour of a single BRT station. The complete station geometry is inspired by the Calle 100 station of TransMilenio in Bogotá, Colombia


## Input files
The simulator uses input files to obtain the information regarding the geometry of the system and the definition of bus services.

### conf/stoplist.txt
This file contains the list of stations to be defined in the system. Each station should appear twice, one for each possible direction. The file has two columns:
- `int` the station ID, this is the common key that will be used in all othe configuration files. The IDs should start with 0 and have +1 increments.
- `string` the name of the station. For future reference, the name of the station will be stored.

### conf/stopdefinition.txt
This file contains the list of all possible doors at a station. Each line represents a station and must contain the following information separated by spaces:
- `int` the station ID, which must be the same than in the `conf/stoplist.txt` file.
- A succession of `int` `int` numbers for each of the doors of the station. The first integer number represents the position, in m, of the door in the corridor (understood as the position of the bus front when stopped at the door); the second integer is either 0 if the door does not support biarticulated buses, and 1 if the door does support biarticulated buses.


### conf/servicelist.txt
This file contains the list of bus service to be defined in the system, it has two columns:
- `int` The ID of the bus service, this is the common key that will be used in all the other service configuration files. The IDs should start with 0 and have +1 increments.
- `string` The name of the bus service, bus services moving in opposite directions must have a different ID and, preferably, a different name.

### conf/servicedefinition.txt
This file containg the information about the stops of a bus service, each line must contain the following information separated by spaces:
- `int` The service ID, which must be the same than in the `servicelist.txt` file.
- `int` The point where the buses servicing this line will appear in the system. In case the position is occupied, the algorithm will try to place the bus a distance `max(busL)` away. If the algorithm does not find space to place the bus, it will place it at the origin and will raise a warning error.
- Next, a succession of pairs `int` `int` will appear for each station where the service makes a stop. The first integer number corresponds to the ID of the station, the second corresponds to the ID of the door at the station where the bus will make the stop. The ID of the doors are assigned according to their appearance in the stopdefinition file, the first door will have ID 0, the second will have ID 1 and so on.

### conf/servicedetails.txt
This file contains the detailed information about each of the bus services in the system. Each line represents a bus service and must contain the following information separated by a space:
- `int` The service ID, which must be the same than in the `servicelist.txt` file.
- `float` the average service headway, $h$, in seconds. At each time step, the buses will be introduced into the system using a Poisson distribution with the headway as the mean.
- `float` the base dwell time, $b$, in seconds.
- `float` the headway dependent dwell time, $\nu$. In our model we assume that the larger the headway, the larger the occupation in the bus and the larger the dwell time.
- `float` the width of the dwell time distribution function, $w$. There is a random component in the dwell time. At each stop, the dwell time will be computed using a normal distribution with mean:
$$\tau = b + h\nu$$
and with standard deviation:
$$\sigma = w\tau$$
- `int` the percentage of biarticulated buses assigned to the bus service. If this number is larger than 0, the bus service cannot be assigned to a wagon without support for biarticulated buses.

### ['conf/lanes_wagon_%d.txt'%i for i in range(len(wagons))]
These are the lane configuration files for each of the wagons at the station, here each column represents a lane, each row represents a cell along the corridor. A 0 indicates that the lane is not available for circulation, a 1 indicates that the lane is available.

### ['conf/lanes_wagon_%d.txt'%i for i in range(len(wagons))]
These are the lane configuration files for each of the wagons at the station, here each column represents a lane (0, main lane; 1, stopping lane), each row represents a cell along the corridor. A 0 indicates that the lane is not available for circulation, a 1 indicates that the lane is available.

### ['conf/RC_wagon_%d.txt'%i for i in range(len(wagons))]
These are the change to the right files, here each column represents a lane (0, main lane; 1, stopping lane), each row represents a cell along the corridor. A 1 means that it is possible to change lanes to the right (decrease the lane), a 0 means that it is not possible to decrease the lane.

### ['conf/LC_wagon_%d.txt'%i for i in range(len(wagons))]
These are the change to the left files, here each column represents a lane (0, main lane; 1, stopping lane), each row represents a cell along the corridor. A 1 means that it is possible to change lanes to the left (increase the lane), a 0 means that it is not possible to increase the lane.

### ['conf/EL_wagon_%d.txt'%i for i in range(len(wagons))]
These are the end of lane files, here each column represents a lane (0, main lane; 1, stopping lane), each row represents a cell along the corridor. The value in each row-column corresponds to the distance to the next end of lane from the current position. When there is no lane end, a 1000 will appear.

### conf/V.txt
This is the maximum speed file, here each column represents a lane (0, main lane; 1, stopping lane), each row represents a cell along the corridor. The value in each row-column corresponds to the maximum speed, in m/s, at the current position.