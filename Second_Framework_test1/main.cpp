#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
int GetDistinctRealRootCount(double a, double b, double c);
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
int SolveQuadric(double a, double b , double c){
    double D=b*b-4*a*c;
    if(D<0){
        return 0;
    }
    if(D==0) {
        return 1;
    }
    return 2;
}
int SolveLinear(double b,double c){
if (b==0){
    return 0;
}else{
    return 1;
}
}
void TestQuadric(){
    AssertEqual(GetDistinctRealRootCount(2,2,2),0);
    AssertEqual(GetDistinctRealRootCount(2,0,0),1);
    AssertEqual(GetDistinctRealRootCount(2,0,-2),2);
    AssertEqual(GetDistinctRealRootCount(2,0,2),0);
    AssertEqual(GetDistinctRealRootCount(2,-2,2),0);
    AssertEqual(GetDistinctRealRootCount(-2,0,2),2);
}
void TestLinear(){
    AssertEqual(GetDistinctRealRootCount(0,0,2),0);
    AssertEqual(GetDistinctRealRootCount(0,2,2),1);
    AssertEqual(GetDistinctRealRootCount(0,-2,0),1);
    AssertEqual(GetDistinctRealRootCount(0,2,-2),1);
    AssertEqual(GetDistinctRealRootCount(0,0,-2),0);
    AssertEqual(GetDistinctRealRootCount(0,2,0),1);

}
int GetDistinctRealRootCount(double a, double b, double c) {
if(a==0){
    return SolveLinear(b,c);
}
else{
    return SolveQuadric(a,b,c);
}
}

int main() {
    TestRunner runner;
    runner.RunTest(TestLinear,"TestLinear");
    runner.RunTest(TestQuadric,"TestQuadric");
    return 0;
}
