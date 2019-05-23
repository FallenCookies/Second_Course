#include "database.h"




pair<Date, string> Database::Last(const Date &date)const   {
        if (map1.empty()){
            throw invalid_argument("");
        }
        if (date < (*map1.begin()).first) {
            throw invalid_argument("");
        }
        auto begin=map1.upper_bound(date);
        begin--;
        return make_pair(begin->first, begin->second.back());


}

void Database::Print(ostream &os) const {
    for(const auto& item:map1){
        for (const auto& item2:item.second)
        {
            os<<item.first<<" " << item2 <<endl;
        }
    }
}
