#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border) {
	auto less_or_eq_it = numbers.lower_bound(border);
	if (less_or_eq_it == numbers.begin()) {
		return less_or_eq_it;
	}
	if (less_or_eq_it == numbers.end()) {
		return prev(less_or_eq_it);
	}
	auto prev_it = prev(less_or_eq_it);
	if (*less_or_eq_it - border < border - *prev_it) {
		return less_or_eq_it;
	}
	return prev_it;
}

int main() {
	set<int> numbers = {1, 4, 6};
    cout <<
        *FindNearestElement(numbers, 0) << " " <<
        *FindNearestElement(numbers, 3) << " " <<
        *FindNearestElement(numbers, 5) << " " <<
        *FindNearestElement(numbers, 6) << " " <<
        *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;
  
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}
