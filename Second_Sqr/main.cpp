#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
template <typename T> vector<T> Sqr(const vector<T>& vec);
template <typename T,typename Q> pair<T,Q> Sqr(const pair<T,Q>& pair1);
template <typename T,typename Q> map<T,Q> Sqr(const map<T,Q>& map1);
template <typename T> T Sqr(const T& value);
template <typename T,typename Q> pair<T,Q> operator*(const pair<T,T>& l,const pair<T,T>& r);


template <typename T,typename Q>
pair<T,Q> operator*(const pair<T,Q>& l,const pair<T,Q>& r){
    return make_pair(Sqr(l.first),Sqr(l.second));
};

template <typename T>
vector<T> Sqr(const vector<T>& vec) {
    vector<T> result;
    for (auto item:vec) {
        result.push_back(Sqr(item));
    }
    return result;
}
template <typename T,typename Q>
pair<T,Q> Sqr(const pair<T,Q>& pair1) {
    return make_pair(Sqr(pair1.first),Sqr(pair1.second));
}
template <typename T,typename Q>
map<T,Q> Sqr(const map<T,Q>& map1){
    map<T,Q> result;
    for (auto item:map1){
        result[item.first]=Sqr(item.second);
    }
    return result;
};
template <typename T>
T Sqr(const T& value){
    return value*value;
}
int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}