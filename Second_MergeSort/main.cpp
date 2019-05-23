#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int Count =0;
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin > 1) {
        vector<typename RandomIt::value_type> main(range_begin, range_end);
        auto it_middle_first = main.begin() + (range_end - range_begin) / 3;
        auto it_middle_second = it_middle_first+(range_end - range_begin) / 3;
        MergeSort(main.begin(), it_middle_first);
        MergeSort(it_middle_first, it_middle_second);
        MergeSort(it_middle_second,main.end());
        vector<typename RandomIt::value_type> tmp;
        merge(main.begin(), it_middle_first, it_middle_first,
              it_middle_second, back_inserter(tmp));
        merge(tmp.begin(),tmp.end(),it_middle_second,main.end(),range_begin);
    } else {
        return;
    }

}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 2};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}