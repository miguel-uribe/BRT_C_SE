#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <array>

// This file defines all the system parameters
const int Dt=1;     // This is the time unit
const int Dx=1;     // This is the space unit
const  std::array<int, 2> a2 = {17, 27};    // The bus length, equivalent to 30m
const int vmax=17;          // The maximun velocity corresponding to 3.6*Dx/Dt km/h
const float p=0.25;          // The random breaking probability
const int Dh=1e+6;      // The position of inactive buses
const int D0=10;           // The default dwell time
const int Nparam = 19;    // Number of integer parameters for each bus
const int Nbool = 2;        // Number of boolean parameters for each bus
const int ncheck = 10; // the number of buses to check when looking for the lateral gaps
const int nparpass = 7;  // the number of parameters a passenger has
const int MaxDwell = 30;  // the maximum dwell time
const int NStations = 2; // The total number of stations in the system
const int NLines = 15; // The total number of routes
const int L = 2280; // The length of the system
const int nkind = 6; // The different kind of station schemes
const int Nmax = 2; // The maximum number of lanes
const int fleet = 200; // The maximum numbers of moving buses
#endif