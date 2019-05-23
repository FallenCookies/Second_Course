#include <iostream>
#include <map>
#include <vector>
using namespace std;
//enum class Lang {
//    DE, FR, IT
//};
//struct Region {
//  string std_name;
//  string parent_std_name;
//  map<Lang, string> names;
//  int64_t population;
//};
bool operator<(const Region& lhs,const Region& rhs){
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
           tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}
int FindMaxRepetitionCount(const vector<Region>& regions){
    map <Region,int> counter;
    int result=1;
    if(regions.empty())
        return 0;
    for (const auto& item:regions){
        counter[item]+=1;
        if(result<counter[item])
            result=counter[item];
    }
    return result;
}

//int main() {
//    cout << FindMaxRepetitionCount({
//                                           {
//                                                   "Russia",
//                                                   "Eurasia",
//                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                                                   89
//                                           }, {
//                    "Russia",
//                    "Eurasia",
//                    {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                    89
//                                           }, {
//                    "Russia",
//                    "Eurasia",
//                    {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                    89
//                                           }, {
//                    "Russia",
//                    "Eurasia",
//                    {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                    87
//                                           }, {
//                                                   "Russia",
//                                                   "Eurasia",
//                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                                                   86
//                                           },
//                                   }) << endl;
//
//    cout << FindMaxRepetitionCount({
//                                           {
//                                                   "Moscow",
//                                                   "Russia",
//                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                                                   89
//                                           }, {
//                                                   "Russia",
//                                                   "Eurasia",
//                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
//                                                   89
//                                           }, {
//                                                   "Moscow",
//                                                   "Russia",
//                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
//                                                   89
//                                           }, {
//                                                   "Moscow",
//                                                   "Toulouse",
//                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                                                   89
//                                           }, {
//                                                   "Moscow",
//                                                   "Russia",
//                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
//                                                   31
//                                           },
//                                   }) << endl;
//
//    return 0;
//}