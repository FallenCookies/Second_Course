#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<string> SplitIntoWords(const string& s){
  auto it=s.begin();
  auto tmp_it=s.begin();
  vector<string> result;
    while (it!=s.end()){
        if (*it==' '|| it+1==s.end()){
            if(it+1==s.end()){
                string str(tmp_it,it+1);
                result.push_back(str);
                break;
            }
            string str(tmp_it,it);
            result.push_back(str);
            tmp_it=it+1;

        }
        it++;
    }

    return result;
}
int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}