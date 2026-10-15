#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

class Date
{
private:
    int month;
    int day;
    int year;

public:
    Date(int m, int d, int y);

    static Date today();
    void displayDate() const;
    void displayDate(ostream& out) const;
    Date addDays(int days) const;
};

#endif