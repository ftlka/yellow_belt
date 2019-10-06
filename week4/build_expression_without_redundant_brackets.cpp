#include <iostream>
#include <string>
#include <queue>

using namespace std;


int main() {
	int x;
	int n;
	cin >> x >> n;

	string thrash;
	getline(cin, thrash);

	queue<string> q;
	int prev_priority = 2;

	for (int i = 0; i < n; i++) {
		string operation;
		getline(cin, operation);
		int cur_priority;
		if (operation[0] == '*' || operation[0] == '/') {
			cur_priority = 1;
		} else {
			cur_priority = 0;
		}
		if (cur_priority > prev_priority) {
			cout << "(";
			q.push(") " + operation);
		} else {
			q.push(" " + operation);
		}
		prev_priority = cur_priority;
	}

	cout << to_string(x);

	for (int i = 0; i < n; i++) {
		string cur = q.front();
		q.pop();
		cout << cur;
	}
	cout << endl;
	return 0;
}
