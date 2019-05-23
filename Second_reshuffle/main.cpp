#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;
void print(const vector<int>& v){
    for(auto item:v){
        cout<<item<<" ";
    }
    cout<<endl;
}
int factorial (int x)
{
    if( x == 0 ) return 1;
    return x * factorial (x - 1);
}
void next_permutation_print( vector<int>& v,int n){
    int k =factorial(n);
    for (int i = 0; i <k ; ++i) {
        prev_permutation(v.begin(),v.end());
        print(v);
    }
}
int main() {
    int n;
    cin>>n;
    vector<int> v;
    for (int i = 1; i <=n ; ++i) {
        v.push_back(i);
    }
    next_permutation_print(v,n);
    return 0;
}