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

class Person {
public:
    void ChangeFirstName(int year, const string& first_name);
    void ChangeLastName(int year, const string& last_name);
    string GetFullName(int year);
};

void TestEmpty(const string& hint) {
    int year = 1900;
    Person p;
    AssertEqual(p.GetFullName(year), "Incognito", hint);
    AssertEqual(p.GetFullName(year), "Incognito", hint);
    AssertEqual(p.GetFullName(year), "Incognito", hint);
}

void TestCreatesPerson(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeFirstName(year, "Alice");
    p.ChangeLastName(year, "DaleLace");
    AssertEqual(p.GetFullName(year + 1), "Alice DaleLace", hint);
}

void TestCreatesPersonSameYear(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeFirstName(year, "Alice");
    p.ChangeLastName(year, "DaleLace");
    AssertEqual(p.GetFullName(year), "Alice DaleLace", hint);
}

void TestChangeFirstName(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeFirstName(year, "Alice");
    p.ChangeLastName(year, "DaleLace");
    p.ChangeFirstName(year + 1, "Eve");
    AssertEqual(p.GetFullName(year + 1), "Eve DaleLace", hint);
}

void TestChangeLastName(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeFirstName(year, "Alice");
    p.ChangeLastName(year, "DaleLace");
    p.ChangeLastName(year + 1, "Ferrell");
    AssertEqual(p.GetFullName(year + 1), "Alice Ferrell", hint);
}

void TestChangeFullName(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeFirstName(year, "Alice");
    p.ChangeLastName(year, "DaleLace");
    p.ChangeFirstName(year + 1, "Eve");
    p.ChangeLastName(year + 1, "Ferrell");
    AssertEqual(p.GetFullName(year + 1), "Eve Ferrell", hint);
}

void TestNoFirstName(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeLastName(year, "DaleLace");
    AssertEqual(p.GetFullName(year), "DaleLace with unknown first name", hint);
}

void TestNoLastName(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeFirstName(year, "Alice");
    AssertEqual(p.GetFullName(year), "Alice with unknown last name", hint);
}

void TestBackInTime(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeFirstName(year, "Alice");
    p.ChangeLastName(year, "DaleLace");
    AssertEqual(p.GetFullName(year - 1), "Incognito", hint);
}

void TestChangedInPast(const string& hint) {
    int year = 1900;
    Person p;
    p.ChangeFirstName(year, "Alice");
    p.ChangeLastName(year, "DaleLace");
    p.ChangeFirstName(year - 2, "Eve");
    p.ChangeLastName(year - 2, "Ferrell");
    AssertEqual(p.GetFullName(year), "Alice DaleLace", hint);
    AssertEqual(p.GetFullName(year - 1), "Eve Ferrell", hint);
}

int main() {
    TestRunner tr;
    tr.RunTest(TestEmpty, "TestEmpty");
    tr.RunTest(TestCreatesPerson, "TestCreatesPerson");
    tr.RunTest(TestCreatesPersonSameYear, "TestCreatesPersonSameYear");
    tr.RunTest(TestChangeFirstName, "TestChangeFirstName");
    tr.RunTest(TestChangeLastName, "TestChangeLastName");
    tr.RunTest(TestChangeFullName, "TestChangeFullName");
    tr.RunTest(TestNoFirstName, "TestNoFirstName");
    tr.RunTest(TestNoLastName, "TestNoLastName");
    tr.RunTest(TestBackInTime, "TestBackInTime");
    tr.RunTest(TestChangedInPast, "TestChangedInPast");

    return 0;
}
