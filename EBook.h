#ifndef EBOOK_H
#define EBOOK_H

#include "Book.h"

class EBook : public Book
{
private:
    double fileSizeMB;

public:
    EBook(string t, string a, Genre g, double size);

    void displayInfo() const override;
    double getFileSizeMB() const;
};

#endif