#include "Transaction.h"

Transaction::Transaction(int pId, string title, Date d, Date due)
    : date(d), dueDate(due)
{
    patronId = pId;
    bookTitle = title;
}

void Transaction::displayTransaction() const
{
    cout << "Patron ID: " << patronId << endl;
    cout << "Book: " << bookTitle << endl;

    cout << "Checkout Date: ";
    date.displayDate();
    cout << endl;

    cout << "Due Date: ";
    dueDate.displayDate();
    cout << endl;
}

void Transaction::saveToFile(ostream& out) const
{
    out << "Patron ID: " << patronId << endl;
    out << "Book: " << bookTitle << endl;

    out << "Checkout Date: ";
    date.displayDate(out);
    out << endl;

    out << "Due Date: ";
    dueDate.displayDate(out);
    out << endl;
    out << "--------------------" << endl;
}
