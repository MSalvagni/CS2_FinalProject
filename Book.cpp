#include "Book.h"

Book::Book(string t, string a, Genre g)
{
    title = t;
    author = a;
    genre = g;
    status = BookStatus::Available;
}

void Book::displayInfo() const
{
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;

    if (genre == Genre::Fiction)
    {
        cout << "Genre: Fiction" << endl;
    }
    else if (genre == Genre::NonFiction)
    {
        cout << "Genre: Non-Fiction" << endl;
    }
    else if (genre == Genre::Mystery)
    {
        cout << "Genre: Mystery" << endl;
    }
    else if (genre == Genre::Science)
    {
        cout << "Genre: Science" << endl;
    }
    else if (genre == Genre::Biography)
    {
        cout << "Genre: Biography" << endl;
    }

    if (status == BookStatus::Available)
    {
        cout << "Status: Available" << endl;
    }
    else if (status == BookStatus::CheckedOut)
    {
        cout << "Status: Checked Out" << endl;
    }
}

bool Book::operator==(const Book& other) const
{
    return title == other.title && author == other.author;
}

ostream& operator<<(ostream& os, const Book& b)
{
    os << "Title: " << b.title << endl;
    os << "Author: " << b.author << endl;

    return os;
}

void Book::setStatus(BookStatus s)
{
    status = s;
}

BookStatus Book::getStatus() const
{
    return status;
}

string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

Genre Book::getGenre() const
{
    return genre;
}