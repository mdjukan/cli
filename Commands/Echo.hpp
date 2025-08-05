#pragma once
#include "../Command.hpp"
#include "../Lexer.hpp"
#include <vector>
#include <iostream>
using namespace std;

//echo [argument] [redirections < in.file, > out.file, >> out.file]
class Echo : public Command {
    public:
    Echo(const vector<Lexer::Token> &__tokens);
    void run() override ;
};