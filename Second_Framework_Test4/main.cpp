#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

bool IsPalindrom(const string& str) {
    if(str.empty())
        return true;
    if(str.size()==1)
        return true;
    uint64_t j=str.size()-1;
    for (int i = 0; i <str.size() ; ++i) {
        if(str[i]!=str[j]){
            return false;
        }
        j--;
    }
    return true;
}
void Testlist(){
    AssertEqual(IsPalindrom(""), true);
    AssertEqual(IsPalindrom("a"), true);
    AssertEqual(IsPalindrom("aa"), true);
    AssertEqual(IsPalindrom("aba"), true);
    AssertEqual(IsPalindrom("madam"), true);
    AssertEqual(IsPalindrom("level"), true);
    AssertEqual(IsPalindrom("level1"), false);
    AssertEqual(IsPalindrom("level2"), false);
    AssertEqual(IsPalindrom("KekeS"), false);
    AssertEqual(IsPalindrom("l e l"), true);
    AssertEqual(IsPalindrom(" l e l "), true);
    AssertEqual(IsPalindrom("1233215"), false);
    AssertEqual(IsPalindrom("1 "), false);
    AssertEqual(IsPalindrom("1      1"), true);
    AssertEqual(IsPalindrom("12345321"), false);
    AssertEqual(IsPalindrom("l el"), false);
    AssertEqual(IsPalindrom("l el "), false);
    AssertEqual(IsPalindrom(" l el "), false);
    AssertEqual(IsPalindrom("ekek"), false);
    AssertEqual(IsPalindrom("keke"), false);

}

int main() {
    TestRunner runner;
    runner.RunTest(Testlist,"TestList");
    return 0;
}
