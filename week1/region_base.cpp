#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


enum class Lang {
  DE, FR, IT
};


struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};


bool operator==(const Region& a, const Region& b) {
	return tie(a.std_name, a.parent_std_name, a.names,
		a.population) == tie(b.std_name, b.parent_std_name,
		b.names, b.population);
};


bool operator<(const Region& a, const Region& b) {
	return tie(a.std_name, a.parent_std_name, a.names,
		a.population) < tie(b.std_name, b.parent_std_name,
		b.names, b.population);
}


int FindMaxRepetitionCount(const vector<Region>& regions) {
	if (!regions.size()) {
		return 0;
	}
	
	int max_repetition = 1;
	set<Region> s(regions.begin(), regions.end());
	for (auto current_region : s) {
		int current_repetition = count(regions.begin(), regions.end(), current_region);
		max_repetition = max(max_repetition, current_repetition);
	}

	return max_repetition;
};


int main() {
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;
  
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;
  
  return 0;
}
