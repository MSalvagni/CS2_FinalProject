#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include "LibraryException.h"
#include "Book.h"
#include "Patron.h"
#include "Transaction.h"

using namespace std;

class Library
{
private:
    vector<Book*> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

    map<int, Patron> patronMap;

public:
    Library();

    ~Library();

    void displayBooks() const;
    void displayPatrons() const;
    void displayTransactions() const;

    void searchByAuthor(string author) const;
    void searchByGenre(Genre genre) const;

    void addBook(Book* book);
    void addPatron(Patron patron);

    void loadBooks(string filename);
    void loadPatrons(string filename);
    void loadTransactions(string filename);

    void saveBooks(string filename) const;
    void savePatrons(string filename) const;
    void saveTransactions(string filename) const;

    Patron* findPatronById(int id);

    Book* findBookByTitle(string title) const;

    void checkoutBook(Patron& patron, Book* book, Date date);
    void returnBook(Patron& patron, Book* book);
};

template <typename T>
void saveToFile(string filename, const vector<T>& items)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        throw LibraryException("Could not save file.");
    }

    for (const T& item : items)
    {
        file << item << endl;
    }

    file.close();
}

template <typename T>
vector<T> loadLinesFromFile(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        throw LibraryException("Could not open file.");
    }

    vector<T> items;
    T item;

    while (getline(file, item))
    {
        items.push_back(item);
    }

    file.close();
    return items;
}

template <typename T>
void saveLinesToFile(string filename, const vector<T>& items)
{
    ofstream file(filename);

    if (!file.is_open())
    {
        throw LibraryException("Could not save file.");
    }

    for (const T& item : items)
    {
        file << item << endl;
    }

    file.close();
}

#endif