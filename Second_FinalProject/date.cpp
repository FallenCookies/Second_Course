
#include <iostream>
#include <sstream>
#include "date.h"

using namespace std;
enum class DataType {
    MONTH,
    YEAR,

};
Date ParseDate(istream& is ) {
    string unparsed_date;
    is>>unparsed_date;
    string tmp;
    int count=0;
    DataType tk=DataType::YEAR;

    Date d;
    for (uint32_t i=0;i<unparsed_date.length();i++){

        if(unparsed_date[i]!='-' && i!=unparsed_date.length()) {
            tmp += unparsed_date[i];
        }else{
            switch(tk){
                case (DataType::YEAR):{
                    d.set_year(stoi(tmp));
                    tk=DataType ::MONTH;
                    break;
                }
                case (DataType ::MONTH):{
                    d.set_month(stoi(tmp));
                    d.set_day(stoi(unparsed_date.substr(i+1,unparsed_date.length()-1)));
                    break;
                }

            }
            tmp="";
        }

    }

    return d;

}
int Date::GetYear() const  {
    return year;
}
int Date::GetDay() const {
    return day;
}
int Date::GetMonth() const {
    return month;
}
void Date::set_day(const int& Day_) {
    day=Day_;
}
void Date::set_month(const int& month_) {
    month=month_;
}
void Date::set_year(const int& year_) {
    year=year_;
}




