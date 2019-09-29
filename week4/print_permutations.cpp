#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print_vector(const vector<int>& nums) {
	for (int num : nums) {
		cout << num << ' '; 
	}
	cout << endl;
}


void print_permutations(int num) {
	vector<int> nums;
	while (num > 0) {
		nums.push_back(num);
		num--;
	}
	print_vector(nums);
	while (prev_permutation(nums.begin(), nums.end())) {
		print_vector(nums);
	}
}


int main() {
	int num;
	cin >> num;
	print_permutations(num);
	return 0;
}