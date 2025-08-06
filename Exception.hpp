#pragma once
#include <exception>
#include <string>
#include <sstream>
using namespace std;

class Exception {
    protected:
    string message;

    public:
    virtual string getMessage() = 0;

    Exception(const string &message) : message(message) {}
};


class LexicalError : public Exception {
    private:
    string &instruction;
    string::iterator errorBegin, errorEnd;
    public:
    LexicalError(string &instruction, const string &message,
    string::iterator errorBegin, string::iterator errorEnd)
     : Exception(message), instruction(instruction), errorBegin(errorBegin), errorEnd(errorEnd)
     {}

    string getMessage() override ;
};

class SyntaxError : public Exception {
    public:
    SyntaxError(const string &message) : Exception(message) {}
    string getMessage() override ;
};

class RuntimeError : public Exception {
    public:
    RuntimeError(const string &message) : Exception(message) {}
    string getMessage() override;
};