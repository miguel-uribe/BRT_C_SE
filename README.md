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
- `string` The name of the bus service, bus services moving in opposite directions must have a different ID and, preferably, a different name

### conf/servicedefinition.txt
This file containg the information about the stops of a bus service, each line must contain the following information separated by spaces:
- `int` The service ID, which must be the same than in the `routelist.txt` file.
- `int` The point where the buses servicing this line will appear in the system. In case the position is occupied, the algorithm will try to place the bus a distance `max(busL)` away. If the algorithm does not find space to place the bus, it will place it at the origin and will raise a warning error.
- Next, a succession of pairs `int` `int` will appear for each station where the service makes a stop. The first integer number corresponds to the ID of the station, the second corresponds to the ID of the door at the station where the bus will make the stop.
