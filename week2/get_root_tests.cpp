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

int GetDistinctRealRootCount(double a, double b, double c);

void Test2Zeros(const string& hint) {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1.0), 0, hint);
    AssertEqual(GetDistinctRealRootCount(0, 1.0, 0), 1, hint);
    AssertEqual(GetDistinctRealRootCount(1.0, 0, 0), 1, hint);
}

void Test2ZerosNeg(const string& hint) {
    AssertEqual(GetDistinctRealRootCount(0, 0, -1.0), 0, hint);
    AssertEqual(GetDistinctRealRootCount(0, -1.0, 0), 1, hint);
    AssertEqual(GetDistinctRealRootCount(-1.0, 0, 0), 1, hint);
}

void TestAIsZero(const string& hint) {
    AssertEqual(GetDistinctRealRootCount(0, 1.0, 1.0), 1, hint);
    AssertEqual(GetDistinctRealRootCount(0, -1.0, 1.0), 1, hint);
    AssertEqual(GetDistinctRealRootCount(0, 1.0, -1.0), 1, hint);
    AssertEqual(GetDistinctRealRootCount(0, -1.0, -1.0), 1, hint);
}

void TestDIsZero(const string& hint) {
    AssertEqual(GetDistinctRealRootCount(1.0, -4.0, 4.0), 1, hint);
    AssertEqual(GetDistinctRealRootCount(-1.0, -4.0, -4.0), 1, hint);
    AssertEqual(GetDistinctRealRootCount(1.0, 4.0, 4.0), 1, hint);
    AssertEqual(GetDistinctRealRootCount(-1.0, 4.0, -4.0), 1, hint);
}

void TestDIsPositive(const string& hint) {
    AssertEqual(GetDistinctRealRootCount(2.0, 7.0, 3.0), 2, hint);
    AssertEqual(GetDistinctRealRootCount(2.0, -7.0, 3.0), 2, hint);
    AssertEqual(GetDistinctRealRootCount(-2.0, 7.0, -3.0), 2, hint);
    AssertEqual(GetDistinctRealRootCount(-2.0, -7.0, -3.0), 2, hint);

    AssertEqual(GetDistinctRealRootCount(-5.0, 7.0, 10.0), 2, hint);
    AssertEqual(GetDistinctRealRootCount(-5.0, -7.0, 10.0), 2, hint);
	AssertEqual(GetDistinctRealRootCount(5.0, 7.0, -10.0), 2, hint);
    AssertEqual(GetDistinctRealRootCount(5.0, -7.0, -10.0), 2, hint);
}

void TestDIsNegative(const string& hint) {
    AssertEqual(GetDistinctRealRootCount(5.0, 7.0, 10.0), 0, hint);
    AssertEqual(GetDistinctRealRootCount(5.0, -7.0, 10.0), 0, hint);
	AssertEqual(GetDistinctRealRootCount(5.0, 7.0, 10.0), 0, hint);
    AssertEqual(GetDistinctRealRootCount(5.0, -7.0, 10.0), 0, hint);
}

int main() {
    TestRunner tr;
    tr.RunTest(Test2Zeros, "Test2Zeros");
    tr.RunTest(Test2ZerosNeg, "Test2ZerosNeg");
    tr.RunTest(TestAIsZero, "TestAIsZero");
    tr.RunTest(TestDIsZero, "TestDIsZero");
    tr.RunTest(TestDIsPositive, "TestDIsPositive");
    tr.RunTest(TestDIsNegative, "TestDIsNegative");

    return 0;
}
