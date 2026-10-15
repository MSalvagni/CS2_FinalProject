
#include <iostream>
#include <limits>
#include <string>

#include "Library.h"
#include "PrintedBook.h"
#include "EBook.h"
#include "LibraryException.h"

using namespace std;

int main()
{
    Library library;

    try
    {
        library.loadBooks("books.txt");
        library.loadPatrons("patrons.txt");
        library.loadTransactions("transactions.txt");
    }
    catch (const LibraryException& e)
    {
        cout << "Error loading library data: "
             << e.what() << endl;
        return 1;
    }

    int choice = -1;

    do
    {
        cout << "\n===== Library Management System =====" << endl;
        cout << "1. Display all books" << endl;
        cout << "2. Display all patrons" << endl;
        cout << "3. Search books by author" << endl;
        cout << "4. Search books by genre" << endl;
        cout << "5. Display transactions" << endl;
        cout << "6. Check out a book" << endl;
        cout << "7. Return a book" << endl;
        cout << "0. Save and exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            library.displayBooks();
            break;

        case 2:
            library.displayPatrons();
            break;

        case 3:
        {
            string author;

            cout << "Enter author name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, author);

            library.searchByAuthor(author);
            break;
        }

        case 4:
        {
            int genreChoice;

            cout << "\n1. Fiction" << endl;
            cout << "2. NonFiction" << endl;
            cout << "3. Mystery" << endl;
            cout << "4. Science" << endl;
            cout << "5. Biography" << endl;
            cout << "Choose a genre: ";

            cin >> genreChoice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid genre choice." << endl;
                break;
            }

            switch (genreChoice)
            {
            case 1:
                library.searchByGenre(Genre::Fiction);
                break;

            case 2:
                library.searchByGenre(Genre::NonFiction);
                break;

            case 3:
                library.searchByGenre(Genre::Mystery);
                break;

            case 4:
                library.searchByGenre(Genre::Science);
                break;

            case 5:
                library.searchByGenre(Genre::Biography);
                break;

            default:
                cout << "Invalid genre choice." << endl;
            }

            break;
        }

        case 5:
            library.displayTransactions();
            break;

        case 6:
        {
            int patronId;
            string title;

            cout << "Enter patron ID: ";
            cin >> patronId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid patron ID." << endl;
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter book title: ";
            getline(cin, title);

            Patron* patron = library.findPatronById(patronId);
            Book* book = library.findBookByTitle(title);

            if (patron == nullptr)
            {
                cout << "Patron not found." << endl;
                break;
            }

            if (book == nullptr)
            {
                cout << "Book not found." << endl;
                break;
            }

            try
            {
                library.checkoutBook(*patron, book, Date::today());
                cout << "Checkout successful." << endl;
            }
            catch (const LibraryException& e)
            {
                cout << "Error: " << e.what() << endl;
            }

            break;
        }

        case 7:
        {
            int patronId;
            string title;

            cout << "Enter patron ID: ";
            cin >> patronId;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid patron ID." << endl;
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter book title: ";
            getline(cin, title);

            Patron* patron = library.findPatronById(patronId);
            Book* book = library.findBookByTitle(title);

            if (patron == nullptr)
            {
                cout << "Patron not found." << endl;
                break;
            }

            if (book == nullptr)
            {
                cout << "Book not found." << endl;
                break;
            }

            library.returnBook(*patron, book);
            break;
        }

        case 0:
            try
            {
                library.saveBooks("books.txt");
                library.savePatrons("patrons.txt");
                library.saveTransactions("transactions.txt");

                cout << "Library data saved. Goodbye!" << endl;
            }
            catch (const LibraryException& e)
            {
                cout << "Error saving data: "
                     << e.what() << endl;
            }

            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
