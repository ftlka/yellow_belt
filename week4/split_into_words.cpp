#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


vector<string> SplitIntoWords(const string& s) {
	vector<string> splitted_words;
	auto it = begin(s);
	auto space = begin(s);
	while (it != end(s) && space < end(s)) {
		space = find_if(it, end(s),
			[](int ch) {
				return ch == ' ';
			}
		);
		splitted_words.push_back(string(it, space));
  		it = space + 1;
  	}
  	return splitted_words;
}

int main() {
	string s = "C Cpp Java Python";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
 	}
 	cout << endl;
  
 	return 0;
}
