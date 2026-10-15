#ifndef LIBRARYEXCEPTION_H
#define LIBRARYEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class LibraryException : public exception
{
private:
    string message;

public:
    LibraryException(string msg)
        : message(msg)
    {
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

#endif