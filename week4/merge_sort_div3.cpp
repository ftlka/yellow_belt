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
	int third = copied.size() / 3;
	auto first_third = next(copied.begin(), third);
	auto second_third = next(copied.begin(), 2 * third);

	MergeSort(copied.begin(), first_third);
	MergeSort(first_third, second_third);
	MergeSort(second_third, copied.end());

	vector<typename RandomIt::value_type> tmp_vec;
	merge(
		copied.begin(), first_third,
		first_third, second_third,
		back_inserter(tmp_vec)
	);

	merge(
		tmp_vec.begin(), tmp_vec.end(),
		second_third, copied.end(),
		range_begin
	);
}

int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
