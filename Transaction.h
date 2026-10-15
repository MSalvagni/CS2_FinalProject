#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include "Date.h"

using namespace std;

class Transaction
{
private:
    int patronId;
    string bookTitle;
    Date date;
    Date dueDate;

public:
    Transaction(int pId, string title, Date d, Date due);

    void displayTransaction() const;
    void saveToFile(ostream& out) const;
};

#endif