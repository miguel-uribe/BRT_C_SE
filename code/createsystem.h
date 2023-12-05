#ifndef CREATE_SYSTEM
#define CREATE_SYSTEM

//# include "linesC.h"
# include "parameters.h"
# include "stationC.h"
# include <vector>
# include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sstream>
#include <string>

struct System
{
    lineC Lines[NLines];  
    stationC Stations[NStations];
};


auto createsystem(std::string stoplist, std::string stopdefinitions, std::string routelist, std::string routedefinitions, std::string routeheadways){
    
    // Creating the structure of the system
    System SYSTEM;
    
    // creating the list of stations in the system
    std::ifstream stoplist_f, stopdefinitions_f;
    stoplist_f.open(stoplist);
    stopdefinitions_f.open(stopdefinitions);
    std::string Line;
    std::string read;
    int ID, begin, end;
    std::string stName;
    while (std::getline(stoplist_f,Line)){
        std::istringstream iss(Line);
        iss>>read;
        ID = std::stoi(read);
        iss>>read;
        stName = read;
        SYSTEM.Stations[ID] = stationC(stName);
    }
    // opening the definition file to include the stops of each station
    while (std::getline(stopdefinitions_f,Line)){
        std::istringstream iss(Line);
        iss>>read;
        ID = std::stoi(read);
        while(iss>>read){
            int stoppos = (int) std::round(1.0*std::stoi(read)/Dx);
            iss>>read;
            int biart = std::stoi(read);
            SYSTEM.Stations[ID].addstop(stoppos, biart);
        }
    }

    stoplist_f.close();
    stopdefinitions_f.close();

    // Creating the list of routes in the system and loading their headways
    std::ifstream routelist_f, routedefinitions_f, routeheadways_f;
    routelist_f.open(routelist);
    routedefinitions_f.open(routedefinitions);
    routeheadways_f.open(routeheadways);
    float dist_k, dist_theta;
    std::string lName;
    while (std::getline(routelist_f,Line)){
        std::istringstream iss(Line);
        iss>>read;
        ID = std::stoi(read);
        iss>>read;
        lName = read;
        SYSTEM.Lines[ID] = lineC(lName);
    }
    // loading the headway information

    while (std::getline(routeheadways_f,Line)){
        std::istringstream iss(Line);
        iss>>read;
        ID = std::stoi(read);
        iss>>read;
        int headway = std::stoi(read);
        iss>>read;
        int dwelltime = std::stoi(read);
        iss>>read;
        float dwellhwy = std::stof(read);
        iss>>read;
        float dwellwidth = std::stof(read);
        iss>>read;
        int biart = std::stoi(read);
        SYSTEM.Lines[ID].headway = headway;
        SYSTEM.Lines[ID].dwelltime = dwelltime;
        SYSTEM.Lines[ID].dwellhway = dwellhwy;
        SYSTEM.Lines[ID].dwellwidth = dwellwidth;
        SYSTEM.Lines[ID].biart = biart;
        // we now calculate the distribution parameters
        dist_k = dwelltime*dwelltime/(dwellwidth*dwellwidth);
        dist_theta = (dwellwidth*dwellwidth)/dwelltime;
        // we update the distribution
        SYSTEM.Lines[ID].distribution.param(std::gamma_distribution<double>::param_type(dist_k, dist_theta));

    }
    // loading the information regarding the stops
    std::vector<int> stationIDs;
    std::vector<int> wagonIDs;
    while (std::getline(routedefinitions_f,Line)){
        std::istringstream iss(Line);
        iss>>read;
        ID = std::stoi(read);
        iss>>read;
        int origin = std::stoi(read);
        iss>>read;
        int end = std::stoi(read);
        iss>>read;
        int measBeg = std::stoi(read);
        iss>>read;
        int measEnd = std::stoi(read);
        SYSTEM.Lines[ID].origin =(int) std::round(1.0*origin/Dx);
        SYSTEM.Lines[ID].end = (int) std::round(1.0*end/Dx);
        SYSTEM.Lines[ID].measBeg =(int) std::round(1.0*measBeg/Dx);
        SYSTEM.Lines[ID].measEnd = (int) std::round(1.0*measEnd/Dx);

        while(iss>>read){
            int stopID = std::stoi(read);
            iss>>read;
            int wagonID = std::stoi(read);
            stationIDs.push_back(stopID);
            wagonIDs.push_back(wagonID);
        }
        SYSTEM.Lines[ID].setstopx(stationIDs, wagonIDs, SYSTEM.Stations);
        stationIDs.clear();
        wagonIDs.clear();

        
    }

    routelist_f.close();
    routedefinitions_f.close();
    routeheadways_f.close();



    return (SYSTEM);

}

// this script loads the configuration files and creates the corresponding lane configuration, the factor is a multiplying factor to be applied in case it is needed
std::array<std::array<int, 2*L>, Nmax> loadconffile(std::string root, float factor){
    // creating the array
    std::array<std::array<int, 2*L>, Nmax> lanes;
    // opening the file
    std::string filename = "../conf/";
    filename = filename + root + ".txt";
    std::ifstream file(filename);
    std::string str;
    float val;
    int i = 0;
    while (std::getline(file,str)){
        // retrieving the origin and destination stations
        std::istringstream iss(str);
        for (int j=0; j<Nmax; j++){
            iss>>val;
            lanes[j][i] = (int) val*factor;
        }
        i++;
    }
    file.close();
    return lanes;
}


// this script loads the configuration files and creates the corresponding lane configuration when there are many different kinds of configuration files, the factor is a multiplying factor to be applied in case it is needed
std::array<std::array<std::array<int, 2*L>, Nmax>, nkind> loadconffilekind(std::string root, float factor){

    // creating the array
    std::array<std::array<std::array<int, 2*L>, Nmax>, nkind> lanes;
    // opening the files
    for (int k=0; k<nkind; k++){
        std::string filename = "../conf/";
        filename = filename + root +"_wagon_"+std::to_string(k)+".txt";
        //std::cout<<filename<<std::endl;
        std::ifstream file(filename);
        std::string str;
        float val;
        int i = 0;
        while (std::getline(file,str)){
            // retrieving the value for each position
            std::istringstream iss(str);
            for (int j=0; j<Nmax; j++){
                iss>>val;
                lanes[k][j][i] = (int) val*factor;
            }
            i++;
        }
        file.close();
    }
    return lanes;
}


#endif