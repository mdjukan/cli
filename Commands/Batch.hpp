#pragma once
#include "../Command.hpp"

//batch [argument] ...redirections
class Batch : public Command {
    public:
    Batch(const vector<Lexer::Token> &__tokens);
    void run() override ;
};