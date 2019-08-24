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

bool IsPalindrom(const string& s);

void TestEmpty(const string& hint) {
    AssertEqual(IsPalindrom(""), 1, hint);
}

void TestSingleLetter(const string& hint) {
    AssertEqual(IsPalindrom("a"), 1, hint);
}

void TestSpaceBefore(const string& hint) {
    AssertEqual(IsPalindrom(" a"), 0, hint);
}

void TestSpaceAfter(const string& hint) {
    AssertEqual(IsPalindrom("a "), 0, hint);
}

void TestOdd(const string& hint) {
    AssertEqual(IsPalindrom("aba"), 1, hint);
}

void TestEven(const string& hint) {
    AssertEqual(IsPalindrom("abba"), 1, hint);
}

void TestNotAPalindrom(const string& hint) {
    AssertEqual(IsPalindrom("abaababa"), 0, hint);
}

void TestLowerUpper(const string& hint) {
    AssertEqual(IsPalindrom("aA"), 0, hint);
}

void TestJustSpaces(const string& hint) {
    AssertEqual(IsPalindrom("          "), 1, hint);
}

void TestSpecialCharacters(const string& hint) {
    AssertEqual(IsPalindrom("|*_*&_*|"), 0, hint);
}

int main() {
    TestRunner tr;
    tr.RunTest(TestEmpty, "TestEmpty");
    tr.RunTest(TestSingleLetter, "TestSingleLetter");
    tr.RunTest(TestSpaceBefore, "TestSpaceBefore");
    tr.RunTest(TestSpaceAfter, "TestSpaceAfter");
    tr.RunTest(TestOdd, "TestOdd");
    tr.RunTest(TestEven, "TestEven");
    tr.RunTest(TestNotAPalindrom, "TestNotAPalindrom");
    tr.RunTest(TestLowerUpper, "TestLowerUpper");
    tr.RunTest(TestJustSpaces, "TestJustSpaces");
    tr.RunTest(TestSpecialCharacters, "TestSpecialCharacters");

    return 0;
}
