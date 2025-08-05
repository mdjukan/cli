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
    ostream *out();
    istream *in();
    void inputStreamFromFile(string fileName);
    void inputStreamFromStrLit(string strLit);

    public:
    virtual void run() = 0;
    Command(const vector<Lexer::Token> &tokens) : tokens(tokens) {}
    static shared_ptr<Command> fromString(string &instr);
};