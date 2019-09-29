#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_begin + 1 >= range_end) {
		return;
	}

	vector<typename RandomIt::value_type> copied(range_begin, range_end);
	int half = copied.size() / 2;
	auto half_iter = next(copied.begin(), half);

	MergeSort(copied.begin(), half_iter);
	MergeSort(half_iter, copied.end());

	merge(
		copied.begin(), half_iter,
		half_iter, copied.end(),
		range_begin
	);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
