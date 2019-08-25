#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
	auto first_negative = find_if(begin(numbers), end(numbers),
		[](int num) {
			return num < 0;
		});
	while (first_negative != begin(numbers)) {
		first_negative--;
		cout << *first_negative << " ";
	}
}

int main() {
	PrintVectorPart({6, 1, 8, -5, 4});
	cout << endl;
	PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
	cout << endl;
	PrintVectorPart({6, 1, 8, 5, 4});
	cout << endl;
	return 0;
}

