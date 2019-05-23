#include "phone_number.h"
#include <iostream>
#include <sstream>
PhoneNumber::PhoneNumber(const string &international_number) {
    enum areas {Country,City,Local};
    areas a=areas::Country;
    if (international_number.empty())
        throw invalid_argument("Empty");
    if (international_number[0]!='+')
        throw invalid_argument("No Plus");
    for (int i = 1; i <international_number.size() ; ++i) {
        switch (a) {
            case Country:
                if (international_number[i] == '-') {
                    a = areas::City;
                    break;
                }
                country_code_ += international_number[i];
                break;
            case City:
                if (international_number[i] == '-') {
                    a = areas::Local;
                    break;
                }
                city_code_ += international_number[i];
                break;
            case Local:
                local_number_ += international_number[i];
                break;
        }
    }
    if(country_code_.empty() || city_code_.empty() || local_number_.empty()) {
        cout << "+" + country_code_ + '-' + city_code_ + '-';
        throw invalid_argument("Some emptiness:");
    }
}

string PhoneNumber::GetInternationalNumber() const {
    return "+"+country_code_+'-'+city_code_+'-'+local_number_;
}
string PhoneNumber::GetCityCode() const {
    return city_code_;
}
string PhoneNumber::GetCountryCode() const {
    return country_code_;
}
string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}