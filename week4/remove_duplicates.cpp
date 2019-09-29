#include <vector>
#include <string>
#include <set>
#include <iostream>

using namespace std;

template <typename T>
void RemoveDuplicates(vector<T>& elements) {
	set<T> seen;
	auto it = elements.begin();
	while (it < elements.end()) {
		if (seen.count(*it) == 0) {
			seen.insert(*it);
			it++;
		} else {
			it = elements.erase(it);
		}
	}
}

int main() {
	vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
    RemoveDuplicates(v1);
    for (int x : v1) {
        cout << x << " ";
    }
    cout << endl;
  
    vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
    RemoveDuplicates(v2);
    for (const string& s : v2) {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}
