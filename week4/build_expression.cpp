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

	for (int i = 0; i < n; i++) {
		string operation;
		getline(cin, operation);
		q.push(operation);
		cout << "(";
	}

	cout << to_string(x);

	for (int i = 0; i < n; i++) {
		cout << ")";
		string cur = q.front();
		q.pop();
		cout << " " << cur;
	}
	cout << endl;
	return 0;
}
