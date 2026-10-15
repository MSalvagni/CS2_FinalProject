#include "Patron.h"

Patron::Patron(string n, int i)
{
    name = n;
    id = i;
}

void Patron::borrowBook(Book* b)
{
    borrowedBooks.push_back(b);
}

void Patron::returnBook(Book* b)
{
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
    {
        if (*it == b)
        {
            borrowedBooks.erase(it);
            break;
        }
    }
}

void Patron::displayPatron() const
{
    cout << "Patron ID: " << id << endl;
    cout << "Name: " << name << endl;

    cout << "Borrowed Books:" << endl;

    for (Book* book : borrowedBooks)
    {
        book->displayInfo();
    }
}

bool Patron::operator==(const Patron& other) const
{
    return id == other.id;
}

ostream& operator<<(ostream& os, const Patron& p)
{
    os << "Patron ID: " << p.id << endl;
    os << "Name: " << p.name << endl;

    return os;
}

int Patron::getId() const
{
    return id;
}

string Patron::getName() const
{
    return name;
}