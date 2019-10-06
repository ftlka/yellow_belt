#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <utility>

using namespace std;


int find_last_available_year(const set<int>& years, int year) {
    auto lower_or_eq = years.upper_bound(year);
    if (lower_or_eq != years.begin()) {
        lower_or_eq = prev(lower_or_eq);
    } else if (year < *lower_or_eq) {
        return -1;
    }
    return *lower_or_eq;
}


class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        f_years.insert(year);
        first_names[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        l_years.insert(year);
        last_names[year] = last_name;
    }

    string GetFullName(int year) {
        int f_year = find_last_available_year(f_years, year);
        int l_year = find_last_available_year(l_years, year);

        if (f_year == -1 && l_year == -1) {
            return "Incognito";
        }
        if (f_year == -1) {
            return last_names[l_year] + " with unknown first name";
        }
        if (l_year == -1) {
            return first_names[f_year] + " with unknown last name";
        }
        return first_names[f_year] + " " + last_names[l_year];
    }
private:
    set<int> f_years;
    set<int> l_years;
    map<int, string> first_names;
    map<int, string> last_names;
};

int main() {
    Person person;
  
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }
  
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
  
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}
