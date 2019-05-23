#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
        db_bus[bus]=stops;
        for (const auto& item:stops){
            db_stops[item].push_back(bus);

        }
    }

    BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const  {
        BusesForStopResponse result;
        result.stop = stop;
        if(db_stops.count(stop)==0)
            return result;
        result.buses = db_stops.at(stop);
        return result;
    }

    StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const  {
        StopsForBusResponse result;
        result.bus=bus;
        if(db_bus.count(bus)==0)
            return result;
        result.stops=db_bus.at(bus);
        result.buses_for_stops=db_stops;
        return result;
    }

   AllBusesResponse BusManager::GetAllBuses() const {
        AllBusesResponse all;
        all.allbuses=db_bus;
        return all;
    }

