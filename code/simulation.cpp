#include <iostream>
#include "linesC.h"
//#include "routeC.h"
#include "createsystem.h"
#include "busC.h"
//#include "passengerC.h"
//#include "fleetsize.h"
#include <array>
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>
#include <thread>
#include <future>


using namespace std;

int main (int argc, char **argv){

    // The arguments list
    // 1 - seed




    //cout<<"Read the input matrix and transfer matrix"<< endl;
    /////////////////////////////////////////////////////////////
    // Creating the system
    System SYSTEM;
    std::string stoplist = "../conf/stoplist.txt";
    std::string stopdefinition = "../conf/stopdefinition.txt";
    std::string routelist = "../conf/servicelist.txt";
    std::string routedefinition = "../conf/servicedefinition.txt";
    std::string routeheadways = "../conf/servicedata.txt";
    
    //cout<<servicefile<<endl;
    SYSTEM = createsystem(stoplist, stopdefinition, routelist, routedefinition, routeheadways);


    for (auto & line: SYSTEM.Stations){
        cout<<line.display()<<endl;
    }

    cout<<"Created the system"<< endl;   
    

    //////////////////////////////////////////////////////////////////
    /////////// Loading the lane information
    ///////////////////////////////////////////
    // Reading the configuration files
    // INFO:: In all these arrays, the first element addresses the lane, the second one the x position
    
    
    array<array<int, 2*L>, Nmax> V;
    V = loadconffile("V", 1.0*Dt/Dx);
    

    array<array<array<int, 2*L>, Nmax>, nkind> lanes, LC, RC, EL;
    lanes = loadconffilekind("lanes", 1);
    LC = loadconffilekind("LC", 1);
    RC = loadconffilekind("RC", 1);
    EL = loadconffilekind("EL", 1.0/Dx);
    
    cout<<"Loaded the configuration files"<<endl;
    
    /////////////////////////////////////////////////////////////
    // the seed
    int seed = stoi(argv[1]);
    std::default_random_engine generator (seed);
    srand(seed);
    //cout<<"Defined the seed"<< endl;   
    ///////////////////////////////////////////////////////////////
    // Creating the bus array
/*
    vector<int> index;
    vector<int> Parked; 
    vector<int> BusesPar[Nparam];
    vector<bool> BusesBool[Nbool];
    deque<int> Queues[2]; // 0 for East, 1 for West
    initializeBusArray(Parked);
    cout<<Parked.size()<<endl;
*/


    ///////////////////////////////////////////////////////////////
    // the simulation parameters

    float cost = 0;
    float flow = 0;
    float occ = 0;
    int ncounts =0;
    vector<float> bussp;

    
    /////////////////////////////////////////////////////////
    // performing the simulation
    /*
    for (int TIME=4*3600; TIME<5*3600;TIME++){      
        // inserting the buses
        //cout<<t<<endl;
        
        populate(BusesPar, SYSTEM, BusesBool, Parked);
        /*
        sortbuses(BusesPar,BusesBool, index);
        buschangelane(BusesPar, BusesBool,SYSTEM, TIME);
        calculategaps(BusesPar,BusesBool);
        //std::cout<<"Bus advanced in test"<<std::endl;
        busadvance(BusesPar,BusesBool,SYSTEM,TIME,RM.matrix, Queues, bussp, cost);
        calculategaps(BusesPar,BusesBool);
    }*/
    
/*
   // cout<<"Finished the simulation"<< endl;   

    /////////////////////////////////////////////////////////
    // calculating the speed for the passengers in the buses
    for (int i = 0; i<BusesPar[0].size(); i++){ // we scan over the buses
        int busID=BusesPar[17][i];
        for (int j = 0; j<BusesPassengers[busID].size(); j++){ // we scan over all passengers in the bus
            int passID = BusesPassengers[busID][j];
            passsp+=fabs(BusesPar[0][i]-SYSTEM.Stations[Passengers[passID][0]].x)/(10*3600-1-Passengers[passID][3]);
        }   
    }

    passsp=passsp/passcount;

    /////////////////////////////////////////////////////////
    // Calculating the bus speed
    // We first calculate the speed for the currently active buses
    for (int i =0; i<BusesPar[0].size(); i++){
        int origin;
        if (BusesPar[18][i]!=10*3600-1){ //we dont take into account buses just released
            if (BusesPar[10][i]>0){ // the bus moves to the east
                origin = SYSTEM.limits[0];
                bussp.push_back(float(BusesPar[0][i]-origin)/(10*3600-1-BusesPar[18][i]));
                //cout<<bussp.back()<<" >0"<<endl;
            } 
            else if (BusesPar[10][i]<0){ // the bus moves to the west
                origin = SYSTEM.limits[1];
                bussp.push_back(float(origin-BusesPar[0][i])/(10*3600-1-BusesPar[18][i]));
                //cout<<bussp.back()<<" <0"<<endl;
            }
            cost+=(10*3600-BusesPar[18][i]);
        }
    }


    float BSP=0;
    for (int i = 0; i<bussp.size(); i++){
        //cout<<bussp[i]<<" "<<BSP<<endl;
        BSP+=bussp[i];
    }

   // cout<<"BSP "<<BSP<<endl;
    /////////////////////////////////////////////////////////
    // normalizing the data
    BSP=BSP/bussp.size();
    cost = cost/3600.0;
    flow = flow/(SYSTEM.limits[1]-SYSTEM.limits[0])/ncounts;
    occ = occ/NStations/ncounts;

    /////////////////////////////////////////////////////////
    // exporting the data
    string filename = "../cpp/sim_results_new/sim_results_";
    // adding the configuration
    filename = filename + argv[24];
    // adding the stop arrangement
    for (int j =12; j<20; j++){
        filename = filename + "_"+argv[j];
    }
    // adding the line times
    for (auto LT: LineTimes){
        filename= filename +"_"+to_string(LT);
    }
    // adding the factor
    filename = filename +"_"+to_string(factor);
    // adding the fleet
    filename = filename +"_"+to_string(fleet);
    // adding the EW fraction
    filename = filename +"_"+to_string(int(100*EWfract))+".txt";

    // opening the file
    ofstream outfile;
    outfile.open(filename, fstream::app);
    outfile<<seed<<" "<<flow<<" "<<passsp<<" "<<BSP<<" "<<occ<<" "<<cost<<endl;
    outfile.close();
   // cout<<"Exported the data"<<endl;*/
}