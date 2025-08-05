#pragma once
#include "../Command.hpp"
#include "../Lexer.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

//date -- bez argumenta, moguce redirekcija izlaznog toka
class Date : public Command {
    public:
    Date(const vector<Lexer::Token> &__tokens);
    void run() override;
};