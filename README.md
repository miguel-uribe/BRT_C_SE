# BRT_C_SE
C++ and Python programming scheme to simulate and optimize the behaviour of a single BRT station. The complete station geometry is inspired by the Calle 100 station of TransMilenio in Bogotá, Colombia


## Input files
The simulator uses input files to obtain the information regarding the geometry of the system and the definition of bus services.

### conf/routelist.txt
This file contains the list of bus service to be defined in the system, it has two columns:
- `int` The ID of the bus service, this is the common key that will be used in all the other service configuration files.
