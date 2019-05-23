#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <map>
using namespace std;

int main() {
    map<string,int> priority={{"+",1},{"-",1},{"*",2},{"/",2}};
    int digit=0;
    int ops_count=0;
    deque<string> result;

    cin>>digit>>ops_count;
    result.push_back(to_string(digit));
    int last_prior=2;
    for (int i = 0; i <ops_count ; ++i) {

        string op;
        int dig;
        cin>>op>>dig;
            if(last_prior<priority[op]){
                result.push_front("(");
                result.emplace_back( ") " + op + " " + to_string(dig));
                last_prior=priority[op];
            } else{
                result.emplace_back( " " + op + " " + to_string(dig));
                last_prior=priority[op];
            }


    }
    for(auto x:result){
        cout<<x;
    };

    return 0;
}