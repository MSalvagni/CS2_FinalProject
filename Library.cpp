#include "Library.h"
#include "LibraryException.h"
#include "PrintedBook.h"
#include "EBook.h"
#include <fstream>
#include <sstream>

Library::Library()
{
}

Library::~Library()
{
    for (Book* book : books)
    {
        delete book;
    }
}

void Library::displayBooks() const
{
    cout << "Books in Library:" << endl;

    for (Book* book : books)
    {
        book->displayInfo();
        cout << endl;
    }
}

void Library::searchByAuthor(string author) const
{
    for (Book* book : books)
    {
        if (book->getAuthor() == author)
        {
            book->displayInfo();
            return;
        }
    }

    cout << "No book found by that author." << endl;
}

void Library::searchByGenre(Genre genre) const
{
    for (Book* book : books)
    {
        if (book->getGenre() == genre)
        {
            book->displayInfo();
        }
    }
}

void Library::displayPatrons() const
{
    cout << "Patrons in Library:" << endl;

    for (const Patron& patron : patrons)
    {
        cout << patron << endl;
    }
}

void Library::addBook(Book* book)
{
    books.push_back(book);
}

void Library::addPatron(Patron patron)
{
    patrons.push_back(patron);
    patronMap.emplace(patron.getId(), patron);
}

void Library::checkoutBook(Patron& patron, Book* book, Date date)
{
    if (book->getStatus() == BookStatus::CheckedOut)
{
    throw LibraryException("Book is already checked out.");
}

    book->setStatus(BookStatus::CheckedOut);
    patron.borrowBook(book);
    Date dueDate = date.addDays(14);
    transactions.push_back(Transaction(patron.getId(), book->getTitle(), date, dueDate));

    cout << "Book checked out successfully." << endl;
}

void Library::returnBook(Patron& patron, Book* book)
{
    if (book->getStatus() == BookStatus::Available)
    {
        cout << "Book is already available." << endl;
        return;
    }

    book->setStatus(BookStatus::Available);
    patron.returnBook(book);

    cout << "Book returned successfully." << endl;
}

void Library::displayTransactions() const
{
    cout << "Transactions:" << endl;

    for (const Transaction& transaction : transactions)
    {
        transaction.displayTransaction();
        cout << endl;
    }
}


void Library::loadBooks(string filename)
{
    vector<string> lines = loadLinesFromFile<string>(filename);

    for (const string& line : lines)
    {
        stringstream ss(line);

        string title;
        string author;
        string genreText;
        string fourthField;
        string statusText = "Available";
        string type;
        string detail;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, genreText, ',');
        getline(ss, fourthField, ',');

        // Support both the old and new file formats.
        if (fourthField == "Available" ||
            fourthField == "CheckedOut")
        {
            statusText = fourthField;
            getline(ss, type, ',');
            getline(ss, detail, ',');
        }
        else
        {
            type = fourthField;
            getline(ss, detail, ',');
        }

        Genre genre;

        if (genreText == "Fiction")
            genre = Genre::Fiction;
        else if (genreText == "NonFiction")
            genre = Genre::NonFiction;
        else if (genreText == "Mystery")
            genre = Genre::Mystery;
        else if (genreText == "Science")
            genre = Genre::Science;
        else if (genreText == "Biography")
            genre = Genre::Biography;
        else
            continue;

        Book* newBook = nullptr;

        if (type == "Printed")
        {
            int pages = stoi(detail);
            newBook = new PrintedBook(title, author, genre, pages);
        }
        else if (type == "EBook")
        {
            double size = stod(detail);
            newBook = new EBook(title, author, genre, size);
        }

        if (newBook != nullptr)
        {
            if (statusText == "CheckedOut")
                newBook->setStatus(BookStatus::CheckedOut);

            addBook(newBook);
        }
    }
}


Book* Library::findBookByTitle(string title) const
{
    for (Book* book : books)
    {
        if (book->getTitle() == title)
        {
            return book;
        }
    }

    return nullptr;
}

void Library::loadPatrons(string filename)
{
    vector<string> lines = loadLinesFromFile<string>(filename);

    for (const string& line : lines)
    {
        stringstream ss(line);

        string idText;
        string name;

        getline(ss, idText, ',');
        getline(ss, name, ',');

        int id = stoi(idText);

        addPatron(Patron(name, id));
    }
}

Patron* Library::findPatronById(int id)
{
    for (Patron& patron : patrons)
    {
        if (patron.getId() == id)
        {
            return &patron;
        }
    }

    return nullptr;
}

void Library::saveBooks(string filename) const
{
    vector<string> lines;

    for (Book* book : books)
    {
        string genreText;

        if (book->getGenre() == Genre::Fiction)
            genreText = "Fiction";
        else if (book->getGenre() == Genre::NonFiction)
            genreText = "NonFiction";
        else if (book->getGenre() == Genre::Mystery)
            genreText = "Mystery";
        else if (book->getGenre() == Genre::Science)
            genreText = "Science";
        else if (book->getGenre() == Genre::Biography)
            genreText = "Biography";

                
        string statusText;

        if (book->getStatus() == BookStatus::Available)
            statusText = "Available";
        else
            statusText = "CheckedOut";

        string line = book->getTitle() + "," +
                    book->getAuthor() + "," +
                    genreText + "," +
                    statusText + ",";


        PrintedBook* printed = dynamic_cast<PrintedBook*>(book);
        EBook* ebook = dynamic_cast<EBook*>(book);

        if (printed != nullptr)
        {
            line += "Printed," + to_string(printed->getPageCount());
        }
        else if (ebook != nullptr)
        {
            line += "EBook," + to_string(ebook->getFileSizeMB());
        }

        lines.push_back(line);
    }

    saveLinesToFile<string>(filename, lines);
}

void Library::savePatrons(string filename) const
{
    vector<string> lines;

    for (const Patron& patron : patrons)
    {
        string line = to_string(patron.getId()) + "," +
                      patron.getName();

        lines.push_back(line);
    }

    saveLinesToFile<string>(filename, lines);
}

void Library::saveTransactions(string filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        throw LibraryException("Could not save transactions file.");
    }

    for (const Transaction& transaction : transactions)
    {
        transaction.saveToFile(file);
    }

    file.close();
}

void Library::loadTransactions(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        // A missing transaction file is allowed on the first run.
        return;
    }

    string line;
    int patronId = 0;
    string bookTitle;
    int checkoutMonth = 0;
    int checkoutDay = 0;
    int checkoutYear = 0;
    int dueMonth = 0;
    int dueDay = 0;
    int dueYear = 0;

    while (getline(file, line))
    {
        if (line.find("Patron ID: ") == 0)
        {
            patronId = stoi(line.substr(11));
        }
        else if (line.find("Book: ") == 0)
        {
            bookTitle = line.substr(6);
        }
        else if (line.find("Checkout Date: ") == 0)
        {
            char slash;
            string dateText = line.substr(15);
            stringstream dateStream(dateText);

            dateStream >> checkoutMonth >> slash
                       >> checkoutDay >> slash >> checkoutYear;
        }
        else if (line.find("Due Date: ") == 0)
        {
            char slash;
            string dateText = line.substr(10);
            stringstream dateStream(dateText);

            dateStream >> dueMonth >> slash
                       >> dueDay >> slash >> dueYear;

            if (patronId > 0 && !bookTitle.empty())
            {
                Date checkoutDate(checkoutMonth, checkoutDay, checkoutYear);
                Date dueDate(dueMonth, dueDay, dueYear);

                transactions.push_back(
                    Transaction(patronId, bookTitle, checkoutDate, dueDate)
                );
            }

            patronId = 0;
            bookTitle.clear();
        }
    }

    file.close();
}


