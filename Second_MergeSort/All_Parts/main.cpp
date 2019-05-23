#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int Count =0;
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin > 1) {
    vector<typename RandomIt::value_type> main(range_begin, range_end);
    auto it_begin = main.begin();
    auto it_end = main.end();
    auto it_middle = it_begin + (range_end - range_begin) / 2;
        MergeSort(it_begin, it_middle);
        MergeSort(it_middle, it_end);
        merge(it_begin, it_middle, it_middle, it_end, range_begin);
    } else {
        return;
    }

}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}