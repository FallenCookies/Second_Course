#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void PrintVectorPart(const vector<int>& numbers){
    auto it=find_if(numbers.begin(),numbers.end(),[](const int& a){
        return a<0;
    });
    while (it!=numbers.begin()){
        it--;
        cout <<*it<<" ";
    }
    cout<<endl;

}
int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    PrintVectorPart({6, 1, 8, 5, 4});
    return 0;
}