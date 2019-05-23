#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        const string& prefix){

    auto it=lower_bound(range_begin,range_end,prefix,[](const string& s, const string& pref){
        string result(s.begin(),s.begin()+pref.size());
        return result<=pref;
    });

    auto it2=lower_bound(range_begin,range_end,prefix,[](const string& s, const string& pref){
        string result(s.begin(),s.begin()+pref.size());
        return result<pref;
    });

    return make_pair(it2,it);
};

int main() {

    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
//
    const auto mt_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
         (mt_result.second - begin(sorted_strings)) << endl;
//
    const auto na_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
         (na_result.second - begin(sorted_strings)) << endl;


    return 0;
}