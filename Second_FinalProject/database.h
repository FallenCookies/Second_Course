#pragma once
#include "date.h"
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <exception>
#include <algorithm>
#include <iomanip>
#include <string>
#include <set>
using namespace std;






class Database {
public:
    void Add( const Date &date, const  string &event) {

            auto pair = set1[date].insert(event);
            if (pair.second) {
                map1[date].push_back(event);

            }


    }

    template<class Predicate>
    int RemoveIf(Predicate predicate) {
            int count = 0;
            for (auto map_iter = map1.begin(); map_iter != map1.end();) {
                int tmp = map_iter->second.size();
                auto it = stable_partition(map_iter->second.begin(), map_iter->second.end(),
                                           [predicate, map_iter](string event) {
                                               return predicate(map_iter->first, event);
                                           });
                for (auto iter = map_iter->second.begin(); iter != it; iter++) {
                    set1[map_iter->first].erase(*iter);
                }
                map_iter->second.erase(map_iter->second.begin(), it);
                count += tmp - map_iter->second.size();
                if (map_iter->second.size() == 0) {
                    map_iter = map1.erase(map_iter);

                } else {
                    map_iter++;
                }
            }
            return count;


    }
    template<class Predicate>
    vector<pair<Date, string>> FindIf(Predicate predicate) const   {
        vector<pair<Date, string>> entries;
        for(auto it=map1.begin();it!=map1.end();it++){
            auto vec_it=it->second.begin();
            while(vec_it!=it->second.end()) {
                vec_it = find_if(vec_it, it->second.end(), [predicate,it](string event) {
                    return predicate(it->first, event);
                });
                if (vec_it != it->second.end()) {
                    entries.push_back(make_pair(it->first, *vec_it));
                    vec_it++;
                }
            }
        }
        return entries;
    }
    pair<Date,string> Last(const Date &date)const  ;
    void Print(ostream& os) const;


public:
    map<Date,vector<string>> map1;
    map<Date,set<string>> set1;

};



