#include <iostream>

using namespace std;


int main() {
    int n;
    int r;
    cin >> n >> r;
    unsigned long long int resulting_weight = 0;
    for (int i = 0; i < n; i++) {
        int w;
        int h;
        int d;
        cin >> w >> h >> d;
        resulting_weight += r * w * h * d;
    }
    cout << resulting_weight << endl;
	return 0;
}