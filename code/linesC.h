#ifndef LINE_C
#define LINE_C

#include "parameters.h"
#include "stationC.h"
#include <cstdlib>
#include <vector>

class lineC{
    public:
        std::string name;
        std::vector<int> stationIDs;
        std::vector<int> wagons;
        std::vector<int> stopx;
        int origin;
        int headway;
        // Dummy constructor
        lineC(){}
        // real constructor
        lineC(std::string NAME){
            name = NAME;
        }

        std::string display (void);
        void setstopx(std::vector<int> &STATIONIDS, std::vector<int> &WAGONS, stationC* STATIONS);
        void setorigin(int ORIGIN);
};

std::string lineC::display (void){
    std::string text = "Line "+ name;
    text = text + ". Headway: " + std::to_string(headway);
    text = text + ". Origin: " + std::to_string(origin);
    text = text + ". Stopping at stations: ";
    for(int i =0; i<stationIDs.size(); i++){
        text = text + std::to_string(stationIDs[i]) +"("+std::to_string(wagons[i])+", "+std::to_string(stopx[i])+")\n";
    }
    return text;
}


void lineC::setstopx(std::vector<int> &STATIONIDS, std::vector<int> &WAGONS, stationC* STATIONS){
    stationIDs = STATIONIDS;
    wagons = WAGONS;
    for (int i = 0; i< stationIDs.size(); i++){
        stopx.push_back(STATIONS[stationIDs[i]].stop_pos[wagons[i]]);
    }
}

void lineC::setorigin(int ORIGIN){
    origin = ORIGIN;
}



/*
def getdestinations(Stations,stationID,Lines):
    # The destinations, lines and origins lists    
    destinationIDs=[]
    lineIDs=[]
    originIDs=[]
    # The origin station
    origin=stationC.getstationbyID(Stations,stationID)
    
    # scanning all the lines stopping in origin
    for lineID in origin.lineIDs:
        # Retrieving the line from lineID
        line=getlinebyID(Lines,lineID)
        # Retrieving the corresponding index for the given station
        i=line.stationIDs.index(stationID)
        # Checking that the index is not the last one
        if i<(len(line.stationIDs)-1):
            # Adding the next station to the destination ID
            destinationIDs.append(line.stationIDs[i+1])
            # Adding the line information
            lineIDs.append(line.ID)
            # Adding the origin information
            originIDs.append(stationID)
    return [destinationIDs,lineIDs,originIDs]*/

/*

class lineC:
    "line class containing all information of a given line"
#    n=0  #the number of lines in the system
    def __init__(self,name,stationIDs,stops,Stations,acc,ID):
        if(len(stops)!=len(stationIDs)):
            print("LineC: The number of stations and the vector of their position do not have the same size")
        self.name=name
        self.stops=stops
        self.stationIDs=stationIDs
        #stationC.updatewagons(Stations,stationIDs,stops)
        self.stopx=[]
        self.acc=acc
        self.ID=ID
#        lineC.n=lineC.n+1
        self.setstopx(Stations)
                
    # Overrides the representation function
    def __repr__(self):
        text="%d: Line %s stopping in stations with ID: "%(self.ID,self.name)
        for i in range(len(self.stationIDs)):
            text=text+" %d(%d);"%(self.stationIDs[i],self.stops[i])
        return text
    
    # Sets the position of all stops of the line
    def setstopx(self,Stations):
        for i in range(len(self.stationIDs)):
            for station in Stations:
                if station.ID==self.stationIDs[i]:
                    stopx=station.x+(self.stops[i]-1)*parameters.Ds+parameters.Dw*(self.acc+abs(self.acc))/(2*abs(self.acc))
                    self.stopx.append(stopx)
                    # Adding the line ID to the station
                    station.lineIDs.append(self.ID)

                    
                    
def getlineindexbyID(Lines,ID):
    for i in range(len(Lines)):
        if Lines[i].ID==ID:
            return i
    print("The given line ID has not been found in the Lines list")
    
def getlinebyID(Lines,ID):
    for line in Lines:
        if line.ID==ID:
            return line
    print("The given line ID has not been found in the Lines list")
    
def getdestinations(Stations,stationID,Lines):
    # The destinations, lines and origins lists    
    destinationIDs=[]
    lineIDs=[]
    originIDs=[]
    # The origin station
    origin=stationC.getstationbyID(Stations,stationID)
    
    # scanning all the lines stopping in origin
    for lineID in origin.lineIDs:
        # Retrieving the line from lineID
        line=getlinebyID(Lines,lineID)
        # Retrieving the corresponding index for the given station
        i=line.stationIDs.index(stationID)
        # Checking that the index is not the last one
        if i<(len(line.stationIDs)-1):
            # Adding the next station to the destination ID
            destinationIDs.append(line.stationIDs[i+1])
            # Adding the line information
            lineIDs.append(line.ID)
            # Adding the origin information
            originIDs.append(stationID)
    return [destinationIDs,lineIDs,originIDs]
        
    
    */
#endif