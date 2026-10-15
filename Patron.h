#ifndef PATRON_H
#define PATRON_H

#include <iostream>
#include <string>
#include <vector>
#include "Book.h"

using namespace std;

class Patron
{
private:
    string name;
    int id;
    vector<Book*> borrowedBooks;

public:
    Patron(string n, int i);

    void borrowBook(Book* b);
    void returnBook(Book* b);

    void displayPatron() const;

    int getId() const;

    string getName() const;

    bool operator==(const Patron& other) const;

    friend ostream& operator<<(ostream& os, const Patron& p);
};

#endif