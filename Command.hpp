#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "Lexer.hpp"
#include <vector>
#include <fstream>
#include "Exception.hpp"
using namespace std;

class Command {
    protected:
    shared_ptr<ostream> outputStream = nullptr; //ako je nullptr onda je outputStream zapravo cout
    shared_ptr<istream> inputStream = nullptr; //ako je nullptr onda je inputStrea zapravo cin
    vector<Lexer::Token> tokens;
    ostream &out();
    istream &in();
    void inputStreamFromFile(string fileName);
    void inputStreamFromStrLit(string strLit);
    void outputStreamFromFile(string fileName);
    void outputStreamFromFileAppend(string fileName);
    void handleRedirects(vector<Lexer::Token>::iterator &tokenIt);

    public:
    virtual void run() = 0;
    virtual void setOutputStream(shared_ptr<ostream> __outputStream);
    void setInputStream(shared_ptr<istream> __inputStream);
    bool writesToStdout();
    Command(const vector<Lexer::Token> &tokens) : tokens(tokens) {}
    static shared_ptr<Command> fromTokens(const vector<Lexer::Token> &tokens);
};