#include "responses.h"
using namespace std;
ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.buses.empty()){
        os<<"No stop";
        return os;
    }
    bool first=true;
    for (const auto& item:r.buses) {
        if(!first) {
            os << " ";
        }
        first = false;
        os << item;
    }
    return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(r.stops.empty()){
        os<<"No bus";
        return os;
    }
    uint64_t count=r.stops.size();
    for (const auto& item:r.stops){
        os<<"Stop "<<item<<": ";
        if(r.buses_for_stops.at(item).size()==1){
            os<<"no interchange";
        }else{
            bool first= true;
            for(const auto& item1:r.buses_for_stops.at(item)){
                if(item1!=r.bus) {
                    if (!first) {
                        os << " ";
                    }
                    first = false;
                    os << item1;
                }
            }
        }
        count--;
        if(count>0)
            os<<endl;
    }
    return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.allbuses.empty()){
        os<<"No buses";
    }
    uint64_t count=r.allbuses.size();
    for(const auto& item:r.allbuses){
        os<<"Bus "<<item.first<<": ";
        bool first=true;
        for(const auto& item2:item.second){
            if(!first) {
                os << " ";
            }
            first = false;
            os << item2;
        }
        count--;
        if(count>0)
            os<<endl;
    }

    return os;
}

