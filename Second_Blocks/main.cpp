#include <iostream>
#include <vector>
using namespace std;
int main() {
    uint64_t n,p;
    cin>>n>>p;
    uint64_t Result=0;
    for (ptrdiff_t i = 0; i <n ; ++i) {
        uint64_t w,h,d;
        cin>>w>>h>>d;
        Result+=w*h*d*p;
    }
    cout<<Result;
    return 0;
}