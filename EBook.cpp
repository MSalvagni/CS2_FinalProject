#include "EBook.h"

EBook::EBook(string t, string a, Genre g, double size)
    : Book(t, a, g)
{
    fileSizeMB = size;
}

void EBook::displayInfo() const
{
    Book::displayInfo();

    cout << "Type: EBook" << endl;
    cout << "File Size: " << fileSizeMB << " MB" << endl;
}

double EBook::getFileSizeMB() const
{
    return fileSizeMB;
}