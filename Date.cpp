#include "Date.h"
#include <ctime>

Date::Date(int m, int d, int y)
{
    month = m;
    day = d;
    year = y;
}


void Date::displayDate(ostream& out) const
{
    out << month << "/" << day << "/" << year;
}

void Date::displayDate() const
{
    cout << month << "/" << day << "/" << year;
}


Date Date::addDays(int days) const
{
    int newMonth = month;
    int newDay = day;
    int newYear = year;

    int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    while (days > 0)
    {
        if (newMonth == 2 &&
            ((newYear % 4 == 0 && newYear % 100 != 0) ||
             newYear % 400 == 0))
        {
            daysInMonth[1] = 29;
        }
        else
        {
            daysInMonth[1] = 28;
        }

        newDay++;
        days--;

        if (newDay > daysInMonth[newMonth - 1])
        {
            newDay = 1;
            newMonth++;

            if (newMonth > 12)
            {
                newMonth = 1;
                newYear++;
            }
        }
    }

    return Date(newMonth, newDay, newYear);
}

Date Date::today()
{
    time_t now = time(nullptr);
    tm* currentTime = localtime(&now);

    return Date(
        currentTime->tm_mon + 1,
        currentTime->tm_mday,
        currentTime->tm_year + 1900
    );
}