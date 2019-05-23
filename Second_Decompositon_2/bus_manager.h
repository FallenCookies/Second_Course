#pragma once

#include "responses.h"
#include <map>
#include <iostream>
using namespace std;
class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops);
    BusesForStopResponse GetBusesForStop(const string& stop) const;
    StopsForBusResponse GetStopsForBus(const string& bus) const;
    AllBusesResponse GetAllBuses() const;
private:
    map <string,vector<string>> db_bus;
    map <string,vector<string>> db_stops;
};