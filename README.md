# BRT_C_SE
C++ and Python programming scheme to simulate and optimize the behaviour of a single BRT station. The complete station geometry is inspired by the Calle 100 station of TransMilenio in Bogotá, Colombia


## Input files
The simulator uses input files to obtain the information regarding the geometry of the system and the definition of bus services.

### conf/stoplist.txt
This file contains the list of stations to be defined in the system. Each station should appear twice, one for each possible direction. The file has two columns:
- `int` the station ID, this is the common key that will be used in all othe configuration files. The IDs should start with 0 and have +1 increments.
- `string` the name of the station. For future reference, the name of the station will be stored.

### conf/stopdefinition.txt


### conf/routelist.txt
This file contains the list of bus service to be defined in the system, it has two columns:
- `int` The ID of the bus service, this is the common key that will be used in all the other service configuration files. The IDs should start with 0 and have +1 increments.
- `string` The name of the bus service, bus services moving in opposite directions must have a different ID and, preferably, a different name

### conf/routedefinition.txt
This file containg the information about the stops of a bus service, each line must contain the following information separated by spaces:
- `int` The service ID, which must be the same than in the `routelist.txt` file.
- `int` The point where the buses servicing this line will appear in the system. In case the position is occupied, the algorithm will try to place the bus a distance `max(busL)` away. If the algorithm does not find space to place the bus, it will place it at the origin and will raise a warning error.
- Next, a succession of pairs `int` `int` will appear for each station where the service makes a stop. The first integer number corresponds to the ID of the station, the second corresponds to the ID of the door at the station where the bus will make the stop.
