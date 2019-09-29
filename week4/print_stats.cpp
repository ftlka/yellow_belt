#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum class Gender {
    FEMALE,
    MALE
};

struct Person {
	int age;
    Gender gender;
    bool is_employed;
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
    }
    vector<typename InputIt::value_type> range_copy(range_begin, range_end);
    auto middle = begin(range_copy) + range_copy.size() / 2;
    nth_element(
    	begin(range_copy), middle, end(range_copy),
        [](const Person& lhs, const Person& rhs) {
            return lhs.age < rhs.age;
        }
    );
    return middle->age;
}

void PrintStats(vector<Person> persons) {
    vector<Person> females;
    copy_if(
    	persons.begin(), persons.end(), back_inserter(females),
    	[](const Person& p) {
    		return p.gender == Gender::FEMALE;
    	}
    );
    vector<Person> employed_females;
    copy_if(
    	females.begin(), females.end(), back_inserter(employed_females),
    	[](const Person& p) {
    		return p.is_employed;
    	}
    );
    vector<Person> unemployed_females;
    copy_if(
    	females.begin(), females.end(), back_inserter(unemployed_females),
    	[](const Person& p) {
    		return !p.is_employed;
    	}
    );

    vector<Person> males;
    copy_if(
    	persons.begin(), persons.end(), back_inserter(males),
    	[](const Person& p) {
    		return p.gender == Gender::MALE;
    	}
    );
    vector<Person> employed_males;
    copy_if(
    	males.begin(),males.end(), back_inserter(employed_males),
    	[](const Person& p) {
    		return p.is_employed;
    	}
    );
    vector<Person> unemployed_males;
    copy_if(
    	males.begin(), males.end(), back_inserter(unemployed_males),
    	[](const Person& p) {
    		return !p.is_employed;
    	}
    );
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    cout << "Median age for females = " << ComputeMedianAge(females.begin(), females.end()) << endl;
    cout << "Median age for males = " << ComputeMedianAge(males.begin(), males.end()) << endl;
    cout << "Median age for employed females = " << ComputeMedianAge(employed_females.begin(), employed_females.end()) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(unemployed_females.begin(), unemployed_females.end()) << endl;
    cout << "Median age for employed males = " << ComputeMedianAge(employed_males.begin(), employed_males.end()) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(unemployed_males.begin(), unemployed_males.end()) << endl;
}

int main() {
	vector<Person> persons = {
		{31, Gender::MALE, false},
        {40, Gender::FEMALE, true},
        {24, Gender::MALE, true},
        {20, Gender::FEMALE, true},
        {80, Gender::FEMALE, false},
        {78, Gender::MALE, false},
        {10, Gender::FEMALE, false},
        {55, Gender::MALE, true},
    };
    PrintStats(persons);
    return 0;
}
