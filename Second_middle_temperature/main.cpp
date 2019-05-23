#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int64_t> base;
    vector<int64_t > result;
    int64_t k=0;
    double sum=0;
    cin>>k;
    for (int64_t i= 0;  i<k ; i++) {
        int64_t value=0;
        cin>>value;
        base.push_back(value);
        sum+=value;
    }
    double mid_value=sum/base.size();
    for (int64_t j = 0; j <base.size() ; ++j) {
        if (base[j]>mid_value)
            result.push_back(j);
    }
    cout<<result.size()<<'\n';
    for (int64_t l = 0; l <result.size() ; ++l) {
        if(l==result.size()-1)
            cout<<result[l];
        else{
            cout<<result[l]<<' ';
        }
    }
    return 0;
}