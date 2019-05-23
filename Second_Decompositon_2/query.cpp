#include "query.h"
istream& operator >> (istream& is, Query& q) {
    string type;
    is>>type;
    if(type=="ALL_BUSES") {
        q.type = QueryType::AllBuses;

    }
    if(type=="NEW_BUS") {
        q.type = QueryType::NewBus;
        is>>q.bus;
        int count;
        is>>count;
        vector<string> result;
        for (int i = 0; i <count ; ++i) {
            string s;
            is>>s;
            result.push_back(s);
        }
        q.stops=result;
    }
    if(type=="BUSES_FOR_STOP"){
        q.type=QueryType::BusesForStop;
        is>>q.stop;
    }
    if(type=="STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is>>q.bus;
    }

    return is;
}