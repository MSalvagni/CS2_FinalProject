#include "PrintedBook.h"

PrintedBook::PrintedBook(string t, string a, Genre g, int pages)
    : Book(t, a, g)
{
    pageCount = pages;
}

void PrintedBook::displayInfo() const
{
    Book::displayInfo();

    cout << "Type: Printed Book" << endl;
    cout << "Pages: " << pageCount << endl;
}

int PrintedBook::getPageCount() const
{
    return pageCount;
}