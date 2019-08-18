#include <iostream>
#include <vector>

using namespace std;


int main() {
    int n;
    cin >> n;
    vector<int> temps(n);
    long long int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> temps[i];
        sum += temps[i];
    }
    long long int average = sum / n;

    int count_days_greater = 0;
    vector<int> indices = {};
    for (int i = 0; i < n; i++) {
        if (temps[i] > average) {
            indices.push_back(i);
            count_days_greater++;
        }
    }
    cout << count_days_greater << endl;
    for (auto i : indices) {
        cout << i << " ";
    }
    cout << endl;
	return 0;
}
