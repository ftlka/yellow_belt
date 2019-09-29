#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;


template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
	vector<T> filtered_vector = {};
	for (auto el : elements) {
		if (el > border) {
			filtered_vector.push_back(el);
		}
	}
	sort(filtered_vector.begin(), filtered_vector.end());
	return filtered_vector;
}

int main() {
	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
		cout << x << " ";
	}
	cout << endl;
	  
	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
	return 0;
}
