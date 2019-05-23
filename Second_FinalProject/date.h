#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class Date{
public:
    Date(){
    }
    Date(int Year, int Month,int Day):day(Day),month(Month),year(Year){
    }
    friend ostream& operator<<(ostream& os, const Date& d){
        os<<setw(4);
        os<<setfill('0');
        os << d.GetYear()<<"-";
        os<<setw(2);
        os << d.GetMonth()<<"-";
        os<<setw(2);
        os << d.GetDay();
        return os;
    }
    friend bool operator<(const Date& lhs, const Date& rhs){
        if(lhs.GetYear()<rhs.GetYear())
            return true;
        if(lhs.GetYear()>rhs.GetYear())
            return false;
        else{
            if (lhs.GetMonth()<rhs.GetMonth())
                return true;
            if (lhs.GetMonth()>rhs.GetMonth())
                return false;
            else
                return lhs.GetDay()<rhs.GetDay();
        }
    }
    friend bool operator>(const Date& lhs, const Date& rhs){
        if(lhs.GetYear()>rhs.GetYear())
            return true;
        if(lhs.GetYear()<rhs.GetYear())
            return false;
        else{
            if (lhs.GetMonth()>rhs.GetMonth())
                return true;
            if (lhs.GetMonth()<rhs.GetMonth())
                return false;
            else
                return lhs.GetDay()>rhs.GetDay();
        }
    }
    friend bool operator>=(const Date& lhs, const Date& rhs){
        return lhs>rhs || lhs==rhs;
    }
    friend bool operator<=(const Date& lhs, const Date& rhs){
        return lhs<rhs || lhs==rhs;
    }
    friend bool operator!=(const Date& lhs, const Date& rhs){
        return !(lhs==rhs);
    }

    friend bool operator==(const Date& lhs, const Date& rhs){
        return lhs.year==rhs.year && lhs.month==rhs.month && lhs.day==rhs.day;

    }
    void  set_day(const int& Day_);
    void  set_month(const int& month_);
    void  set_year(const int& year_);
    int GetYear()const ;
    int GetMonth()const;
    int GetDay()const;


public:
    int day;
    int month;
    int year;
};

Date ParseDate(istream& is);
