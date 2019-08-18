#include <iostream>
#include <map>
#include <vector>

using namespace std;


template <typename T> T Sqr(T x);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);
template <typename Key, typename Value> map<Key, Value> Sqr(const map<Key, Value>& m);
template <typename T> vector<T> Sqr(const vector<T>& v);


template <typename T>
T Sqr(T x) {
	return x * x;
}


template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
	First f = Sqr(p.first);
	Second s = Sqr(p.second);
	return make_pair(f, s);
}


template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
	map<Key, Value> new_map;
	for (auto p : m) {
		new_map[p.first] = Sqr(p.second);
	}
	return new_map;
}


template <typename T>
vector<T> Sqr(const vector<T>& v) {
	vector<T> new_vec(v.size());
	for (int i = 0; i < v.size(); i++) {
		new_vec[i] = Sqr(v[i]);
	}
	return new_vec;
}


int main() {
	// Пример вызова функции
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (auto x : Sqr(v)) {
	  cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
	  cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}	
