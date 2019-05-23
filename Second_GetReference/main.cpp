#include <iostream>
#include <map>
using namespace std;
template<typename F,typename S,typename T>
S& GetRefStrict( map<F,S>& map1, T value){
    try{
        map1.at(value);
    }catch(exception& e){
        throw runtime_error("");
    }
    return map1.at(value);
};

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
    return 0;
}