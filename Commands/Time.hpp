#pragma once
#include "../Command.hpp"
#include "../Lexer.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

//time -- bez argumenta, moguce redirekcija izlaznog toka
class Time : public Command {
    public:
    Time(const vector<Lexer::Token> &__tokens);
    void run() override;
};