#pragma once
#include <map>
#include <vector>
#include <iostream>
using namespace std;


struct BusesForStopResponse {
    string stop;
    vector<string> buses;
};

struct StopsForBusResponse {
    string bus;
    vector<string> stops;
    map <string,vector<string>> buses_for_stops;
};

struct AllBusesResponse {
    map<string,vector<string>> allbuses;
};
ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);