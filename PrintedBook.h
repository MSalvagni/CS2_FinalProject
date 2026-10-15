#ifndef PRINTEDBOOK_H
#define PRINTEDBOOK_H

#include "Book.h"

class PrintedBook : public Book
{
private:
    int pageCount;

public:
    PrintedBook(string t, string a, Genre g, int pages);

    void displayInfo() const override;
    int getPageCount() const;
};

#endif