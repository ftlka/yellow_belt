#include <stdexcept>
#include "phone_number.h"

using namespace std;


PhoneNumber::PhoneNumber(const string &international_number) {
	if (international_number.size() == 0 || international_number[0] != '+') {
		throw invalid_argument("Phone number should start with +");
	}
	int first_position = international_number.find('-');
	if (first_position == -1) {
		throw invalid_argument("Phone number should have at least two dashes");
	}
	country_code_ = international_number.substr(1, first_position - 1);

	string rest_of_number = international_number.substr(first_position + 1, international_number.size());
	int second_position = rest_of_number.find('-');
	if (second_position == -1) {
		throw invalid_argument("Phone number should have at least two dashes");
	}
	city_code_ = rest_of_number.substr(0, second_position);
	local_number_ = rest_of_number.substr(second_position + 1, rest_of_number.size());
	if (country_code_.size() == 0 || city_code_.size() == 0 || local_number_.size() == 0) {
		throw invalid_argument("Empty number");
	}
};

string PhoneNumber::GetCountryCode() const {
	return country_code_;
};

string PhoneNumber::GetCityCode() const {
	return city_code_;
};

string PhoneNumber::GetLocalNumber() const{
	return local_number_;
};

string PhoneNumber::GetInternationalNumber() const {
	return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
};
