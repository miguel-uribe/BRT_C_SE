#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <array>

// This file defines all the system parameters
const int Dt=1;     // This is the time unit
const int Dx=1;     // This is the space unit
const  std::array<int, 2> busL = {17, 27};    // The bus length, equivalent to 30m
const float p=0.15;          // The random breaking probability
const float p0=0.75;         // The random breaking probability when stopped
const int Nparam = 18;    // Number of integer parameters for each bus
const int Nbool = 1;        // Number of boolean parameters for each bus
const int ncheck = 10; // the number of buses to check when looking for the lateral gaps
const int NStations = 2; // The total number of stations in the system
const int NLines = 9; // The total number of routes
const int L = 2280; // The length of the system
const int nkind = 6; // The different kind of station schemes
const int Nmax = 2; // The maximum number of lanes
const int fleet = 500; // The maximum numbers of moving buses
const int vsurr = (int) 9*Dt/Dx;
#endif