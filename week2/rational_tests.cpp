#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

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
void AssertEqual(const T& t, const U& u,
    const string& hint) {
  	if (t != u) {
    	ostringstream os;
    	os << "Assertion failed: " << t << " != " << u
       		<< " hint: " << hint;
    	throw runtime_error(os.str());
  	}
}

inline void Assert(bool b, const string& hint) {
  	AssertEqual(b, true, hint);
}

class TestRunner {
public:
  	template <class TestFunc>
  	void RunTest(TestFunc func, const string& test_name) {
    	try {
	  		func(test_name);
	  		cerr << test_name << " OK" << endl;
		} catch (runtime_error& e) {
	  		++fail_count;
	  		cerr << test_name << " fail: " << e.what() << endl;
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

class Rational {
public:
    Rational();
    Rational(int numerator, int denominator);

    int Numerator() const;
    int Denominator() const;
};

void TestDefaultCreation(const string& hint) {
    Rational rat;
    AssertEqual(rat.Numerator(), 0, hint);
    AssertEqual(rat.Denominator(), 1, hint);
}

void TestNonDefaultCreation(const string& hint) {
    Rational rat(1, 2);
    AssertEqual(rat.Numerator(), 1, hint);
    AssertEqual(rat.Denominator(), 2, hint);
}

void TestAutoSimplification(const string& hint) {
    Rational rat(2, 4);
    AssertEqual(rat.Numerator(), 1, hint);
    AssertEqual(rat.Denominator(), 2, hint);
}

void TestNegativeNum(const string& hint) {
    Rational rat(-1, 7);
    AssertEqual(rat.Numerator(), -1, hint);
    AssertEqual(rat.Denominator(), 7, hint);
}

void TestNegativeDenom(const string& hint) {
    Rational rat(1, -7);
    AssertEqual(rat.Numerator(), -1, hint);
    AssertEqual(rat.Denominator(), 7, hint);
}

void TestMakePositive(const string& hint) {
    Rational rat(-1, -7);
    AssertEqual(rat.Numerator(), 1, hint);
    AssertEqual(rat.Denominator(), 7, hint);
}

void TestZeroNom(const string& hint) {
    Rational rat(0, -7);
    AssertEqual(rat.Numerator(), 0, hint);
    AssertEqual(rat.Denominator(), 1, hint);
}

void TestNegativeSimplification(const string& hint) {
    Rational rat(14, -7);
    AssertEqual(rat.Numerator(), -2, hint);
    AssertEqual(rat.Denominator(), 1, hint);
}

void TestSameSimplification(const string& hint) {
    Rational rat(-100, -100);
    AssertEqual(rat.Numerator(), 1, hint);
    AssertEqual(rat.Denominator(), 1, hint);
}

int main() {
    TestRunner tr;
    tr.RunTest(TestDefaultCreation, "TestDefaultCreation");
    tr.RunTest(TestNonDefaultCreation, "TestNonDefaultCreation");
    tr.RunTest(TestAutoSimplification, "TestAutoSimplification");
    tr.RunTest(TestNegativeNum, "TestNegativeNum");
    tr.RunTest(TestNegativeDenom, "TestNegativeDenom");
    tr.RunTest(TestMakePositive, "TestMakePositive");
    tr.RunTest(TestZeroNom, "TestZeroNom");
    tr.RunTest(TestNegativeSimplification, "TestNegativeSimplification");
    tr.RunTest(TestSameSimplification, "TestSameSimplification");

    return 0;
}
