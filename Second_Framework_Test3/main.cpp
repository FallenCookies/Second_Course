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

int GreatestCommonDivisor(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return GreatestCommonDivisor(b, a % b);
  }
}

//class Rational {
//public:
//  Rational() {  // дробь по умолчанию — 0/1
//    numerator = 0;
//    denominator = 1;
//  }
//  Rational(int new_numerator, int new_denominator) {
//    const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
//    // сократим дробь, разделив числитель и знаменатель на их НОД
//    numerator = new_numerator / gcd;
//    denominator = new_denominator / gcd;
//    // знаменатель должен быть положительным
//    if (denominator < 0) {
//      denominator = -denominator;
//      numerator = -numerator;
//    }
//  }
//
//  int Numerator() const {
//    return numerator;
//  }
//
//  int Denominator() const {
//    return denominator;
//  }
//
//private:
//  int numerator;
//  int denominator;
//};

// поскольку дроби сокращены, достаточно сравнить числители и знаменатели
bool operator == (const Rational& lhs, const Rational& rhs) {
  return lhs.Numerator() == rhs.Numerator() &&
      lhs.Denominator() == rhs.Denominator();
}

// используем обычную формулу сложения дробей, основанную на приведении слагаемых к общему знаменателю
Rational operator + (const Rational& lhs, const Rational& rhs) {
  return {
      lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
      lhs.Denominator() * rhs.Denominator()
  };
}

// вычитание реализуем аналогично сложению
// дублирования кода можно было избежать, определив для класса Rational операцию унарного минуса: тогда разность lhs и rhs можно было бы вычислить           как lhs + (-rhs)
Rational operator - (const Rational& lhs, const Rational& rhs) {
  return {
      lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
      lhs.Denominator() * rhs.Denominator()
  };
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
  return {
      lhs.Numerator() * rhs.Numerator(),
      lhs.Denominator() * rhs.Denominator()
  };
}

// деление равносильно умножению на обратную («перевёрнутую») дробь
Rational operator / (const Rational& lhs, const Rational& rhs) {
  return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

istream& operator >> (istream& is, Rational& r) {
  int n, d;
  char c;
  is >> n >> c >> d;
  if (is && c == '/') {
    r = Rational(n, d);
  }
  return is;
}

ostream& operator << (ostream& os, const Rational& r) {
  return os << r.Numerator() << '/' << r.Denominator();
}

// чтобы сравнить lhs с rhs, сравним их разность с нулём, что равносильно сравнению с нулём числителя
bool operator < (const Rational& lhs, const Rational& rhs) {
  return (lhs - rhs).Numerator() < 0;
}
void TestConstruct(){
    Rational r(5,2);
    AssertEqual(r.Numerator(),5);
    AssertEqual(r.Denominator(),2);
    Rational r1(0,2);
    AssertEqual(r1.Numerator(),0);
    AssertEqual(r1.Denominator(),1);
    Rational r2=Rational();
    AssertEqual(r2.Numerator(),0);
    AssertEqual(r2.Denominator(),1);
}
void TestMinimize(){
    Rational r(5,5);
    AssertEqual(r.Numerator(),1);
    AssertEqual(r.Denominator(),1);
    Rational r1(10,2);
    AssertEqual(r1.Numerator(),5);
    AssertEqual(r1.Denominator(),1);
    Rational r2(5,15);
    AssertEqual(r2.Numerator(),1);
    AssertEqual(r2.Denominator(),3);
}
void TestNegative(){
    Rational r(5,-5);
    AssertEqual(r.Numerator(),-1);
    AssertEqual(r.Denominator(),1);
    Rational r1(-10,2);
    AssertEqual(r1.Numerator(),-5);
    AssertEqual(r1.Denominator(),1);
    Rational r2(5,-15);
    AssertEqual(r2.Numerator(),-1);
    AssertEqual(r2.Denominator(),3);
    Rational r3(-5,-15);
    AssertEqual(r3.Numerator(),1);
    AssertEqual(r3.Denominator(),3);
}
void TestSumm(){
    Rational r1(5,5);
    Rational r2(1,2);
    Rational result=r1+r2;
    AssertEqual(result.Numerator(),3);
    AssertEqual(result.Denominator(),2);
    Rational r3(1,2);
    Rational r4(1,2);
    Rational result1=r3+r4;
    AssertEqual(result1.Numerator(),1);
    AssertEqual(result1.Denominator(),1);
}



int main() {
  TestRunner runner;
  runner.RunTest(TestConstruct,"TestConstruct");
  runner.RunTest(TestMinimize,"TestMinimize");
  runner.RunTest(TestNegative,"TestNegative");
  runner.RunTest(TestSumm,"TestSumm");
  return 0;
}
