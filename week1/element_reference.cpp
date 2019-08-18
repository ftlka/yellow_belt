#include <iostream>
#include <map>
#include <string>

using namespace std;


template <typename Key, typename Value> Value& GetRefStrict(map<Key, Value>& m, Key key);


template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, Key key) {
	if (m.count(key)) {
		return m.at(key);
	}
	throw runtime_error("key is not in the map");
}


int main() {
	map<int, string> m = {{0, "value"}};
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	return 0;
}
